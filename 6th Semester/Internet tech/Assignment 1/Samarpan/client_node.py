import socket
import time
import sys
import getpass

class Client():
    def __init__(self):
        self.serverHost = '127.0.0.1'
        self.serverPort = '8000'
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.managerPassword = 'changeadmin'

    def start(self):
        name = input("Enter your name: ")
        userType = 'g'

        symbol = 'Guest$  '

        hp = input("Enter the host and the port: ")
        hp = hp.split()

        if(hp[0] == self.serverHost and hp[1] == self.serverPort):
            self.socket.connect(('localhost', 8000))
        else:
            sys.exit("Server address is not correct!")

        welcome = self.socket.recv(1024).decode()
        print(welcome)
        time.sleep(0.05)

        self.socket.send(name.encode())
        time.sleep(0.05)

        welcome = self.socket.recv(1024).decode()
        print(welcome)

        while True:
            if userType.lower() == 'm':
                symbol = 'Manager#  '
            else:
                symbol = 'Guest$  '
            userInput = input(symbol)
            userInput = userInput.split()
            length = len(userInput)

            if(userInput[0] == 'end'): 
                self.socket.send(name.encode())
                time.sleep(0.05)
                self.socket.send(userType.encode())
                time.sleep(0.05)
                self.socket.send("end".encode())
                break
                
            count = 0

            while length > count:
                if(userType == 'g' and userInput[count].lower() == 'get'):
                    assert length >= count+2, "Invalid input format!"
                    count += 1
                    attribute = userInput[count]
                    count += 1

                    self.socket.send(name.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('get'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())

                    response = self.socket.recv(1024).decode()
                    print(response)
                
                elif(userType == 'g' and userInput[count].lower() == 'put'):
                    assert length >= count+3, "Invalid input format!"
                    count += 1
                    attribute = userInput[count]
                    count += 1
                    value = userInput[count]
                    count += 1

                    #send to server
                    self.socket.send(name.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('put'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())
                    time.sleep(0.05)
                    self.socket.send(value.encode())

                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                elif(userType == 'g' and userInput[count].lower() == 'makemanager'):
                    password = getpass.getpass(prompt='Enter your manager password: ')
                    if(password == self.managerPassword):
                        userType = 'm'
                        count += 1
                        self.socket.send(name.encode())
                        time.sleep(0.05)
                        self.socket.send('g'.encode())
                        time.sleep(0.05)
                        self.socket.send('u'.encode())
                        time.sleep(0.05)
                    
                    elif(password == 'exit'):
                        break

                    else:
                        print("You have entered a wrong password!")
                    
                    
                elif(userType == 'm' and userInput[count].lower() == 'put'):

                    assert length >= count + 4, "Invalid input format!"
                    count += 1
                    userName = userInput[count]
                    count += 1
                    attribute = userInput[count]
                    count += 1
                    value = userInput[count]
                    count += 1
                    self.socket.send(userName.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('put'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())
                    time.sleep(0.05)
                    self.socket.send(value.encode())
                    time.sleep(0.05)

                    ans = self.socket.recv(1024).decode()
                    print(ans)

                elif(userType == 'm' and userInput[count].lower() == 'get'):

                    assert length >= count + 3, "Invalid input format!"
                    count += 1
                    userName = userInput[count]
                    count += 1
                    attribute = userInput[count]
                    count += 1

                    self.socket.send(userName.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('get'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())
                    time.sleep(0.05)

                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                else:
                    print("Invalid input format!")
                    break
                    


        
if __name__ == "__main__":
    c = Client()
    c.start()