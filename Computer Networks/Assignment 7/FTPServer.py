#!/usr/bin/env python3

import socket


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65300        # Port to listen on (non-privileged ports are > 1023)

print("FTP Server started!!")
while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    print("Listening for a connection on its own port....")
    s.listen()
    conn, addr = s.accept()
    name = conn.recv(1024).decode()
    filename = conn.recv(1024).decode()
    print(name, " with address " , addr , " is requesting file: ", filename)
    file = open(filename, 'r')
    data = file.read()
    conn.send(bytes(data, "utf-8"))
    print("Data sent!")
    s.close()
    print("FTP Server still running!")