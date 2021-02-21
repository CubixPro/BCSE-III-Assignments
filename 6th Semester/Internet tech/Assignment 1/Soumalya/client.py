import socket
import time
import sys
from termcolor import colored



class Client():
    def __init__(self):
        self.serverHost = '127.0.0.1' #localhost
        self.serverPort = '9090'
        self.socket     = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    


    def run(self):
        userType    = input("Do you want to enter as a guest or manager(g/m): ")
        name        = input("Enter Your name: ")
        password    = input("Enter your password: ")


        #################################################
        #asthetics here
        symbol = '#'   if userType.lower() == 'm' else '$'
        color  = 'red' if userType.lower() == 'm' else 'cyan' 

        # this should be bind localhost 9000
        userInput = input(colored(name +  '>>>' + symbol + " ", color))
        userInput = userInput.split()
        

        if(userInput[1] == self.serverHost and userInput[2] == self.serverPort):
            self.socket.connect(('localhost', 9090))
        else: sys.exit("SERVER PORT OR HOST NOT MATCHING...")

        # expect a greeting msg from server
        greetings = self.socket.recv(1024).decode()
        print(greetings)
        time.sleep(0.05)

        # send creds to server
        self.socket.send(name.encode())
        time.sleep(0.05)
        self.socket.send(password.encode())
        

        # received logged in msg from server
        msg = self.socket.recv(1024).decode()
        print(msg)

        while True:
            # now this should be the queries
            symbol = '#'   if userType.lower() == 'm' else '$'
            color  = 'red' if userType.lower() == 'm' else 'cyan'
            userInput = input(colored(name +  '>>>' + symbol + " ", color))
            userInput = userInput.split()
            length = len(userInput)
            if(userInput[0] == 'end'): 
                self.socket.send(name.encode())
                time.sleep(0.05)
                self.socket.send(userType.encode())
                time.sleep(0.05)
                self.socket.send("end".encode())
                break

            # parsing happens here
            counter = 0
            
            # if the function is GET...we need 2 attributes in total
            # i.e GET city_name
            while length > counter:
                if(userType == 'g' and userInput[counter].lower() == 'get'):
                    assert length >= counter+2, "INVALID NUMBER OF ARGUMENTS!!"
                    counter += 1
                    attribute = userInput[counter]
                    counter += 1

                    # send to server
                    self.socket.send(name.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('get'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())

                    # expect an answer from server
                    response = self.socket.recv(1024).decode()
                    print(response)
                
                elif(userType == 'g' and userInput[counter].lower() == 'put'):
                    assert length >= counter+3, "INVALID NUMBER OF ARGUMENTS!!"
                    counter += 1
                    attribute = userInput[counter]
                    counter += 1
                    value = userInput[counter]
                    counter += 1

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

                    # expect an confirmation from server
                    
                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                elif(userType == 'g' and userInput[counter].lower() == 'upgrademe'):
                    password    = input("Enter your manager password: ")
                    userType    = 'm'
                    counter += 1
                    self.socket.send(name.encode())
                    time.sleep(0.05)
                    self.socket.send('g'.encode())
                    time.sleep(0.05)
                    self.socket.send('u'.encode())
                    time.sleep(0.05)
                    self.socket.send(password.encode())
                    time.sleep(0.05)
                
                elif(userType == 'm' and userInput[counter].lower() == 'put'):
                    # put bob cityname Delhi
                    # put my cityname Delhi

                    assert length >= counter + 4, "INVALID NUMBER OF ARGUMENTS!!"
                    counter += 1
                    userName = name if userInput[counter] == 'my' else userInput[counter]
                    counter += 1
                    attribute = userInput[counter]
                    counter += 1
                    value = userInput[counter]
                    counter += 1

                    #send to server
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

                    # expect an confirmation from server
                    ans = self.socket.recv(1024).decode()
                    print(ans)

                elif(userType == 'm' and userInput[counter].lower() == 'get'):
                    # get bob cityname
                    # get my cityname

                    assert length >= counter + 3, "INVALID NUMBER OF ARGUMENTS!!"
                    counter += 1
                    userName = name if userInput[counter] == 'my' else userInput[counter]
                    counter += 1
                    attribute = userInput[counter]
                    counter += 1

                    #send to server
                    self.socket.send(userName.encode())
                    time.sleep(0.05)
                    self.socket.send(userType.encode())
                    time.sleep(0.05)
                    self.socket.send('get'.encode())
                    time.sleep(0.05)
                    self.socket.send(attribute.encode())
                    time.sleep(0.05)

                    # expect an answer from server
                    ans = self.socket.recv(1024).decode()
                    print(ans)
                
                else:
                    print("INVALID COMMAND FOUND AT POSITION " + str(counter+1) + "!!")
                    break
                    




if __name__ == "__main__":
    # print(colored("Hello", "red"))
    # print(colored('World','cyan'))
    c = Client()
    c.run()

    