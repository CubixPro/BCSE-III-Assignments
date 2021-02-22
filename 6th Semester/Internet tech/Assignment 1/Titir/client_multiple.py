import socket
import sys
import pickle
import pdb
import time
from termcolor import colored
from user_management import *

ClientSocket = socket.socket()
host = sys.argv[1] 
port = int(sys.argv[2])
state = "guest>"

i = 3
totalArgLen = len(sys.argv)

print('Waiting for connection')
try:
    ClientSocket.connect((host, port))
except socket.error as e:
    print(str(e))

Response = ClientSocket.recv(1024)
print(Response.decode('utf-8'))
time.sleep(0.05)

#pdb.set_trace()

while i < totalArgLen:
    query = []
    data = ""
    if sys.argv[i] == "put" :
        query = [sys.argv[i], sys.argv[i + 1], sys.argv[i + 2]]
        i = i + 3
    elif sys.argv[i] == "get":
        query = [sys.argv[i], sys.argv[i + 1]]
        i = i + 2
    data = " ".join(query) 
    ClientSocket.sendall(data.encode('utf-8'))
    time.sleep(0.05)
    if query[0] == "get":
        Response = ClientSocket.recv(1024)
        time.sleep(0.05)
        print(Response.decode('utf-8'))



ch = input("Do you want to continue in this client session?(y/n)")
if ch == "y":
    while True:

        if state[0] == 'a':
            text = colored(state, "red")
        else:
            text = colored(state, "cyan")
        inp = input(text)
        if inp == "":
            continue
        query = inp.split(" ")
        err = validate(query, state)
        if err == 0:
            if (query[0] == "get") or (query[0] == "put") or (query[0] == "upgrade") or (query[0] == "login"):
                ClientSocket.sendall(inp.encode('utf-8'))
                time.sleep(0.05)
            if query[0] == "get":
                Response = ClientSocket.recv(1024)
                time.sleep(0.05)
                print(Response.decode('utf-8'))
            if query[0] == "upgrade":
                Response = ClientSocket.recv(1024)
                time.sleep(0.05)
                str = Response.decode('utf-8')
                if (str[0] == '0'):
                    state = "admin$"
                    print(str[1:], end='')
                    use_pass = input()
                    ClientSocket.sendall(use_pass.encode("utf-8"))
                    time.sleep(0.05)
                elif(str[0] == 'A'):
                    print(str)
                else:
                    print("Wrong password")
            if query[0] == "login":
                Response = ClientSocket.recv(1024)
                time.sleep(0.05)
                str = Response.decode('utf-8')
                if str == '0':
                    print("Login successful")
                    state = "admin$"
                
            if query[0] == "exit":
                break
        elif err == 1:
            print("Invalid number of arguments")
        else:
            print("Invalid command")

 


ClientSocket.close()