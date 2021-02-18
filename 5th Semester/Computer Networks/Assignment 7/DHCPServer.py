#!/usr/bin/env python3

import socket


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
OWNport = 65100        # Port to listen on (non-privileged ports are > 1023)
BGPport = 65500

print("DHCP Server started!!")
while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, OWNport))
    print("Listening for a connection on its own port....")
    s.listen()
    conn, addr = s.accept()
    print("Connected by", addr)
    message = conn.recv(1024).decode()
    name = conn.recv(1024).decode()
    print(message, " received from ", addr , " named " , name)
    conn.send(bytes(str(addr), "utf-8"))
    conn.close()
    s.close()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, BGPport))
    s.send(bytes("Request to add host to the log!", "utf-8"))
    message = s.recv(1024).decode()
    print("Message received: ", message)
    s.send(bytes(name, "utf-8"))
    message = s.recv(1024).decode()
    print("Message received: ", message)
    s.send(bytes(str(addr), "utf-8"))
    print(name + " added to the log!")
    print("DHCP Server still running!")