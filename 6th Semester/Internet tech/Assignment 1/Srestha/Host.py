#!/usr/bin/env python3

import socket

Host = '127.0.0.1'  # The server's hostname or IP address

Server = 65000        # The port used by the server

print("Client started!!")
name = input("Enter name of client: ")

while True:
    status = input("Select the status of client- manager or guest/ Exit to exit: ")
    if status == "exit":
        print("Client side is exitting!!!")
        break

    elif status!="manager" and status!="guest":
        print("Invalid input!")
        continue

    command = input("Enter command line: ")
    command_list = command.split()
    if status == "guest":
        if name != command_list[0]:
            print("Guest client cannot access other client's data!")
            continue


    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((Host, Server))
    #print("Connection successful!!!")
    message = s.recv(1024).decode()
    s.send(bytes(str(status), "utf-8"))
    message = s.recv(1024).decode()
    s.send(bytes(str(command_list[0]), "utf-8"))
    i = 1
    while i < len(command_list):
        message = s.recv(1024).decode()
        s.send(bytes(command_list[i], "utf-8"))
        if command_list[i] == "put":
            i = i + 1
            message = s.recv(1024).decode()
            s.send(bytes(command_list[i], "utf-8"))
            message = s.recv(1024).decode()
            i = i + 1
            s.send(bytes(command_list[i], "utf-8"))
            i = i + 1

        else:
            i = i + 1
            message = s.recv(1024).decode()
            s.send(bytes(command_list[i], "utf-8"))
            value = s.recv(1024).decode()
            print(value)
            i = i + 1

    message = s.recv(1024).decode()
    s.send(bytes("close", "utf-8"))
    s.close()







