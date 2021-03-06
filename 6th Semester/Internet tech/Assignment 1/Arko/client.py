import socket
from time import sleep
import sys

class Client():
    def __init__(self):
        self.serverHost = '127.0.0.1'
        self.serverPort = '5555'
        self.socket     = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sleepTime  = 0.1

    def run(self):

        # bind with server 
        print("Bind the client to localhost port 5555")   
        userInput = input(">> bind ")
        userInput = userInput.split()
        
        if(userInput[0] == self.serverHost and userInput[1] == self.serverPort):
            print("Connection established with Server.")
        else: sys.exit("SERVER PORT OR HOST NOT MATCHING...")

        msg = 'Not authorized'

        while msg == 'Not authorized':

            print("Login/Signup :- ")
            userType    = 'g'
            name        = input("Enter Your name: ")
            password    = input("Enter your password: ")

            #close the connection and reconnect
            self.socket.close()
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect(('localhost', 5555))

            # send creds to server
            self.socket.send(name.encode())
            sleep(self.sleepTime)
            self.socket.send(password.encode())   
            sleep(self.sleepTime)    

            # received logged in msg from server
            msg = self.socket.recv(1024).decode()
            print(msg) 
            if msg == "Wrong Password entered.":
                msg = 'Not authorized'

        while True:

            #input the queries
            userInput = input('>> ')
            userInput = userInput.split()
            length = len(userInput)

            counter = 0
            
            #parsing starts from here
            while length > counter:

                if(userType == 'g' and userInput[counter] == 'get'):

                    if length < counter+2:
                        print("Invalid number of arguments.")
                        break

                    counter += 1
                    key = userInput[counter]
                    counter += 1

                    self.socket.send(name.encode())
                    sleep(self.sleepTime)
                    self.socket.send('g'.encode())
                    sleep(self.sleepTime)
                    self.socket.send('get'.encode())
                    sleep(self.sleepTime)
                    self.socket.send(key.encode())
                    sleep(self.sleepTime)

                    response = self.socket.recv(1024).decode()
                    print(response)
                
                elif(userType == 'g' and userInput[counter] == 'put'):

                    if length < counter+3:
                        print("Invalid number of arguments.", counter, length)
                        break

                    counter += 1
                    key = userInput[counter]
                    counter += 1
                    value = userInput[counter]
                    counter += 1

                    self.socket.send(name.encode())
                    sleep(self.sleepTime)
                    self.socket.send('g'.encode())
                    sleep(self.sleepTime)
                    self.socket.send('put'.encode())
                    sleep(self.sleepTime)
                    self.socket.send(key.encode())
                    sleep(self.sleepTime)
                    self.socket.send(value.encode())
                    sleep(self.sleepTime)
                    
                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                elif(userType == 'g' and userInput[counter] == 'upgrade'):

                    password = input("Enter your manager password: ")
                    counter += 1

                    self.socket.send(name.encode())
                    sleep(self.sleepTime)
                    self.socket.send('g'.encode())
                    sleep(self.sleepTime)
                    self.socket.send('up'.encode())
                    sleep(self.sleepTime)
                    self.socket.send(password.encode())
                    sleep(self.sleepTime)

                    ans = self.socket.recv(1024).decode()
                    print(ans)
                    if(ans == "You are now a Manager."):
                        userType = 'm'

                elif(userType == 'm' and userInput[counter] == 'downgrade'):

                    counter += 1

                    self.socket.send(name.encode())
                    sleep(self.sleepTime)
                    self.socket.send('m'.encode())
                    sleep(self.sleepTime)
                    self.socket.send('down'.encode())
                    sleep(self.sleepTime)

                    ans = self.socket.recv(1024).decode()
                    print(ans)
                    userType = 'g'
                
                elif(userType == 'm' and userInput[counter] == 'put'):

                    if length < counter+4:
                        print("Invalid number of arguments.")
                        break

                    counter += 1
                    if userInput[counter] == 'my':
                        userName = name
                    else:
                        userName = userInput[counter]
                    counter += 1
                    key = userInput[counter]
                    counter += 1
                    value = userInput[counter]
                    counter += 1

                    self.socket.send(userName.encode())
                    sleep(self.sleepTime)
                    self.socket.send('m'.encode())
                    sleep(self.sleepTime)
                    self.socket.send('put'.encode())
                    sleep(self.sleepTime)
                    self.socket.send(key.encode())
                    sleep(self.sleepTime)
                    self.socket.send(value.encode())
                    sleep(self.sleepTime)

                    ans = self.socket.recv(1024).decode()
                    print(ans)

                elif(userType == 'm' and userInput[counter] == 'get'):

                    if length < counter+3:
                        print("Invalid number of arguments.")
                        break

                    counter += 1
                    if userInput[counter] == 'my':
                        userName = name
                    else:
                        userName = userInput[counter]
                    counter += 1
                    key = userInput[counter]
                    counter += 1

                    self.socket.send(userName.encode())
                    sleep(self.sleepTime)
                    self.socket.send(userType.encode())
                    sleep(self.sleepTime)
                    self.socket.send('get'.encode())
                    sleep(self.sleepTime)
                    self.socket.send(key.encode())
                    sleep(self.sleepTime)

                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                elif(userInput[counter] == 'logout'): 

                    self.socket.send(name.encode())
                    sleep(self.sleepTime)
                    self.socket.send(userType.encode())
                    sleep(self.sleepTime)
                    self.socket.send('logout'.encode())              
                    sleep(self.sleepTime)
                    return

                else:
                    print("Invalid command found at position " + str(counter+1))
                    break


if __name__ == "__main__":
    c = Client()
    c.run()