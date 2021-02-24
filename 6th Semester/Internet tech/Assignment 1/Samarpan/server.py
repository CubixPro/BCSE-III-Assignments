import socket
from threading import Thread
import time
import sys

class Server:
    def __init__(self):
        self.serverHost     = '127.0.0.1'
        self.serverPort     = '8000'
        self.socket         = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.authDict       = dict()
        self.keyStore       = dict()

    def startThread(self, conn, addr, name):
        thread = Thread(target=self.handleClient, args=(conn, addr, name))
        thread.start()
        thread.join()
    
    def handleClient(self, conn, addr, userName):
        while True:
            name = conn.recv(1024).decode()
            userType = conn.recv(1024).decode()
            operationType = conn.recv(1024).decode()

            if(userType == 'g' and operationType == 'get'):
                attribute = conn.recv(1024).decode()
                if(name != userName):
                    conn.send("Sorry! You need manager privilages for doing this!".encode())
                else:
                    userData = self.keyStore.get(name, 'null')
                    if userData == 'null': 
                        self.keyStore[name] = dict()
                        response = '\n' 
                        conn.send(response.encode())
                    else:
                        result = userData.get(attribute,'null')
                        response = result if result != 'null' else '\n'
                        conn.send(response.encode())
            
            elif(userType == 'g' and operationType == 'put'):

                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                if(name != userName):
                    conn.send("Sorry! You need manager privilages for doing this!".encode())
                else:
                    userData = self.keyStore.get(name, 'null')
                    if userData == 'null': 
                        self.keyStore[name] = dict()

                    self.keyStore[name][attribute] = value
                    conn.send('Data added successfully!'.encode())
            
            elif(userType == 'g' and operationType == 'u'):
                print(f"{name} now has manager privillages!")
                print("-------------------------------------------------------------------------")
                userType = 'm'


            elif(userType == 'm' and operationType == 'put'):
                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                
                userData = self.keyStore.get(name, 'null')
                if userData == 'null': 
                    self.keyStore[name] = dict()

                self.keyStore[name][attribute] = value
                conn.send('Data added successfully!'.encode())
            
            elif(userType == 'm' and operationType == 'get'):
                attribute = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'null')
                if userData == 'null': 
                    self.keyStore[name] = dict()
                    response = '\n' 
                    conn.send(response.encode())
                else:
                    result = userData.get(attribute,'null')
                    response = result if result != 'null' else '\n'
                    conn.send(response.encode())

            elif(operationType == 'end'):
                conn.close()
                print(f"{name} has logged out from the server")
                print("-------------------------------------------------------------------------")
                break

        


    def run(self):

        self.socket.bind(('localhost', 8000))
        self.socket.listen(10)
        print("The server is running on 127.0.0.1 and port 8000!")
        print("-------------------------------------------------------------------------")
        threadPool = []
        while True:
            conn , addr = self.socket.accept()
            conn.send("Welcome to the server!".encode())
            
            name = conn.recv(1024).decode()

            if self.authDict.get(name, 0) == 0:
                self.authDict[name] = 1
                conn.send("Registration successful!".encode())
            else:
                conn.send("Welcome back!".encode())
            print(f"{name} has logged into the server!! ")
            print("-------------------------------------------------------------------------")
            thread = Thread(target=self.handleClient, args=(conn,addr, name))
            threadPool.append(thread)
            thread.start()
        
        for thread in threadPool:
            thread.join()

if __name__ == "__main__":
    server = Server()
    server.run()


