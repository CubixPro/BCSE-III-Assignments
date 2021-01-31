#!/usr/bin/env python3

import socket

Host = '127.0.0.1'  # The server's hostname or IP address

DHCPport = 65100        # The port used by the server
FTPport = 65300        # The port used by the server
BGPport = 65500        # The port used by the server'

print("Host started!!")
OWNaddr = ("","")
name = ""

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((Host, DHCPport))
s.send(bytes("Requesting port number of the host!!" , "utf-8"))
name = input("Enter name of the host: ")
s.send(bytes(name, "utf-8"))
OWNaddr = s.recv(1024).decode()
print("The host address: " , OWNaddr)
s.close()

while True:
    print("Do you wish to:")
    print("1.Request file from FTP server")
    print("2.Send a file to another host")
    print("3.Receive a file from another host")
    print("4.Exit!!!!")
    i = input()
    if i == "4":
        print("Host terminated!")
        break

    elif i == "1":
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((Host, FTPport))
        s.send(bytes(name, "utf-8"))
        filename = input("Enter filename to be searched: ")
        s.send(bytes(filename, "utf-8"))
        data = s.recv(1024).decode()
        print("The contents of the file: ", data)
        s.close()
        continue

    elif i == "2":
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((Host, BGPport))
        s.send(bytes("Requesting file transfer to another host!", "utf-8"))
        message = s.recv(1024).decode()
        print("Message received "+message)
        receiver = input("Enter name of receiver: ")
        s.send(bytes(receiver, "utf-8"))
        data = input("Enter data to be transferred: ")
        s.send(bytes(data, "utf-8"))
        s.close()
        continue

    else:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind((Host, int(OWNaddr[13:-2])))
        s.listen()
        print("Listening for a connection on its own port....")
        conn, addr = s.accept()
        print("Connection established!!")
        message = conn.recv(1024).decode()
        print("Message received "+message)
        conn.send(bytes("Request granted! Send data!", "utf-8"))
        data = conn.recv(1024).decode()
        print("Data received: "+data)
        print("Transmission successful!")
        conn.close()
        s.close()
        continue
