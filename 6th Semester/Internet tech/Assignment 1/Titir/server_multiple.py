import socket
import os
import pickle
from _thread import *
import time
import sys

keyval = {}

masterpass = "admin"
manpass = {}

ServerSocket = socket.socket()
host = '127.0.0.1'
port = 1233

if len(sys.argv) == 2:
    port = int(sys.argv[1])

ThreadCount = 0
try:
    ServerSocket.bind((host, port))
except socket.error as e:
    print(str(e))

print('Waitiing for a Connection..')
ServerSocket.listen(5)


def threaded_client(connection, port):
    state = 'g'
    username = ""
    port = str(port)
    connection.sendall(str.encode('Welcome to the Server\nYour ID is ' + (port) + '\n'))

    time.sleep(0.05)
    while True:
        data = connection.recv(1024)
        fdata = data.decode('utf-8')
        finaldata = fdata.split(" ") 
        try: 
            if state == 'g':
                if finaldata[0] == 'put':
                    keyval[port][finaldata[1]] = finaldata[2]
                elif finaldata[0] == 'get': 
                    reply = keyval[port][finaldata[1]]
                    if reply == None:
                        reply = "Key does not exist"
                    connection.sendall(str.encode(reply))
                    time.sleep(0.05)
                elif finaldata[0] == 'upgrade':
                    if masterpass == finaldata[1]:
                        reply = "0Enter new username and password: "
                        connection.sendall(str.encode(reply))
                        time.sleep(0.05)
                        reply = connection.recv(1024)
                        use_pass = reply.decode('utf-8')
                        use_pass = use_pass.split(' ')
                        manpass[use_pass[0]] = use_pass[1]
                        keyval[use_pass[0]] = keyval[port]
                        state = 'a'
                        username = use_pass[0]
                    else:
                        reply = "1"
                        connection.sendall(str.encode(reply))
                        time.sleep(0.05)
                elif finaldata[0] == "login":
                    if manpass[finaldata[1]] == finaldata[2]:
                        username = finaldata[1]
                        state = 'a'
                        reply = '0'
                    else:
                        reply = '1'
                    connection.sendall(str.encode(reply))
                    time.sleep(0.05)
                else:
                    break
            elif state == 'a':
                if finaldata[0] == 'put' and len(finaldata) == 3:
                    keyval[username][finaldata[1]] = finaldata[2]
                elif finaldata[0] == 'put' and len(finaldata) == 4:
                    keyval[finaldata[1]][finaldata[2]] = finaldata[3]

                elif finaldata[0] == "get":
                    if len(finaldata) == 2:
                        reply = keyval[username][finaldata[1]]
                        if reply == None:
                            reply = "Key does not exist"
                        connection.sendall(str.encode(reply))
                        time.sleep(0.05)
                    elif len(finaldata) == 3:
                        reply = keyval[finaldata[1]][finaldata[2]]
                        if reply == None:
                            reply = "Key does not exist"
                        connection.sendall(str.encode(reply))
                        time.sleep(0.05)
                elif finaldata[0] == "upgrade":
                    reply = "Already manager"
                    connection.sendall(str.encode(reply))
                elif finaldata[0] == "login":
                    if manpass[finaldata[1]] == finaldata[2]:
                        username = finaldata[1]
                        state = 'a'
                        reply = '0'
                    else:
                        reply = '1'
                    connection.sendall(str.encode(reply))
                    time.sleep(0.05)
                else:
                    break
                 
 
        #reply = 'Server Says: ' + finaldata[0]
        #except:

            #print("Inside exception") 
        except:
            print("Inside Exception")
            reply = "Key does not exist" 
            connection.sendall(str.encode(reply))

    connection.close()

while True:
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))
    start_new_thread(threaded_client, (Client, address[1], ))
    keyval[str(address[1])] = {}
    ThreadCount += 1
    print('Thread Number: ' + str(ThreadCount))
ServerSocket.close()