import socket
from threading import Thread

class Server:
    def __init__(self):
        self.serverHost     = '127.0.0.1'
        self.serverPort     = '5555'
        self.socket         = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.keyStore       = dict()
        self.managerPass    = 'makememanager'
        self.authStore      = dict()
    
    def performQuery(self, conn, addr, userName):
        while True:
            name = conn.recv(1024).decode()
            userType = conn.recv(1024).decode()
            opType = conn.recv(1024).decode()

            if(userType == 'g' and opType == 'get'):
                
                attribute = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'NA')

                if userData == 'NA': 
                    self.keyStore[name] = dict()
                    response = 'Not Available' 
                    conn.send(response.encode())
                else:
                    result = userData.get(attribute,'NA')
                    response = result if result != 'NA' else 'Not Available'
                    conn.send(response.encode())
            
            elif(userType == 'g' and opType == 'put'):

                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'NA')

                if userData == 'NA':
                    self.keyStore[name] = dict()

                self.keyStore[name][attribute] = value
                conn.send('Data added to server'.encode())
            
            elif(userType == 'g' and opType == 'up'):

                password = conn.recv(1024).decode()
                if(password == self.managerPass):
                    print(f"{name} has manager privillage now.")
                    conn.send("You are now a Manager.".encode())
                else: 
                    conn.send("Wrong Manager password.".encode())

            elif(userType == 'm' and opType == 'down'):
                print(f"{name} has been downgraded to guest.")
                conn.send("You are downgraded to guest.".encode())
            
            elif(userType == 'm' and opType == 'put'):
                attribute = conn.recv(1024).decode()
                value = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'NA')

                if userData == 'NA': 
                    self.keyStore[name] = dict()

                self.keyStore[name][attribute] = value
                conn.send('Data added to server'.encode())
            
            elif(userType == 'm' and opType == 'get'):
                
                attribute = conn.recv(1024).decode()
                userData = self.keyStore.get(name, 'NA')
                
                if userData == 'NA': 
                    self.keyStore[name] = dict()
                    response = 'Not Available' 
                    conn.send(response.encode())
                else:
                    result = userData.get(attribute,'NA')
                    response = result if result != 'NA' else 'Not Available'
                    conn.send(response.encode())

            elif(opType == 'logout'):
                conn.close()
                print(f"{name} is logged out from the server")
                break

    def run(self):

        self.socket.bind(('localhost', 5555))
        self.socket.listen(10)
        threadPool = []
        print("Server is running at localhost port 5555.")
            
        while True:  
            conn, addr = self.socket.accept()   
            name = conn.recv(1024).decode()
            password = conn.recv(1024).decode()

            if self.authStore.get(name, 'NA') == 'NA':
                self.authStore[name] = password
                conn.send("Greetings from server.\nSuccessfully registered".encode())
                print(f"{name} is registered into the server.")
                thread = Thread(target=self.performQuery, args=(conn, addr, name))
                threadPool.append(thread)
                thread.start()

            elif self.authStore[name] == password:
                conn.send("Greetings from server.\nYou are now logged into the server".encode())
                print(f"{name} is logged into the server.")
                thread = Thread(target=self.performQuery, args=(conn, addr, name))
                threadPool.append(thread)
                thread.start()

            else: 
                print(f"{name}, Please type the correct password.")
                conn.send("Wrong Password entered.".encode())
        
        for thread in threadPool:
            thread.join()

if __name__ == "__main__":
    server = Server()
    server.run()