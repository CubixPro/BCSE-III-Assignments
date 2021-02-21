import socket
from threading import Thread
import time
import sys
from termcolor import colored

class Server:
    def __init__(self):
        self.serverHost     = '127.0.0.1'
        self.serverPort     = '9090'
        self.socket         = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.authDict       = dict()
        self.keyStore       = dict()
        self.managePassword = 'iammanager'

    def startThread(self, conn, addr, name):
        thread = Thread(target=self.handleClient, args=(conn,addr, name))
        thread.start()
        thread.join()
    
    def handleClient(self, conn, addr, userName):
        while True:
            name = conn.recv(1024).decode()
            userType = conn.recv(1024).decode()
            typeOfOp = conn.recv(1024).decode()

            if(userType == 'g' and typeOfOp == 'get'):
                # name should be equal to sent userName
                attribute = conn.recv(1024).decode()
                if(name != userName):
                    conn.send("You are currently logged in as a guest! And don't have access to this data!".encode())
                else:
                    userData = self.keyStore.get(name, 'null')
                    if userData == 'null': # means the user is not in keyStore dict
                        self.keyStore[name] = dict()
                        response = '\n' #prints a blank line in client
                        conn.send(response.encode())
                    else:
                        result = userData.get(attribute,'null')
                        response = result if result != 'null' else '\n'
                        conn.send(response.encode())
            
            elif(userType == 'g' and typeOfOp == 'put'):

                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                if(name != userName):
                    conn.send("You are currently logged in as a guest! And don't have access to this data!".encode())
                else:
                    userData = self.keyStore.get(name, 'null')
                    if userData == 'null': # means the user is not in keyStore dict
                        self.keyStore[name] = dict()

                    self.keyStore[name][attribute] = value
                    conn.send('Data added successfully'.encode())
            
            elif(userType == 'g' and typeOfOp == 'u'):
                password = conn.recv(1024).decode()
                if(password == self.managePassword):
                    userType = 'm'
                    print(f"{name} has now manager privillage!!")
                else: 
                    conn.send("WRONG MANAGER PASSWORD!!".encode())
            
            elif(userType == 'm' and typeOfOp == 'put'):
                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'null')
                if userData == 'null': # means the user is not in keyStore dict
                    self.keyStore[name] = dict()

                self.keyStore[name][attribute] = value
                conn.send('Data added successfully'.encode())
            
            elif(userType == 'm' and typeOfOp == 'get'):
                # name should be equal to sent userName
                attribute = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'null')
                #print(userData)
                if userData == 'null': # means the user is not in keyStore dict
                    self.keyStore[name] = dict()
                    response = '\n' #prints a blank line in client
                    conn.send(response.encode())
                else:
                    result = userData.get(attribute,'null')
                    response = result if result != 'null' else '\n'
                    conn.send(response.encode())

            elif(typeOfOp == 'end'):
                conn.close()
                print(f"{name} is logged out from the server")
                print("*******************************************")
                break

        


    def run(self):

        self.socket.bind(('localhost', 9090))
        self.socket.listen(10)
        threadPool = []
        while True:
            conn , addr = self.socket.accept()
            conn.send("Greetings from server".encode())
            # GET name and password from client and register him
            
            name = conn.recv(1024).decode()
            password = conn.recv(1024).decode()

            if self.authDict.get(name, 0) == 0:
                self.authDict[name] = password
                conn.send("Successfully registered!!".encode())
            else:
                conn.send("You are now logged into the server!!".encode())
            print("*******************************************")
            print(f"{name} is logged into the server!! ")
            #self.startThread(conn, addr, name)
            thread = Thread(target=self.handleClient, args=(conn,addr, name))
            threadPool.append(thread)
            thread.start()
        
        for thread in threadPool:
            thread.join()

if __name__ == "__main__":
    server = Server()
    server.run()


