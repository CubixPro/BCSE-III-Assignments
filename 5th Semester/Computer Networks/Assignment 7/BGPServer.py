#!/usr/bin/env python3

import socket


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65500        # Port to listen on (non-privileged ports are > 1023)

print("BGP Server started!!")
log = dict()
while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    print("Listening for a connection on its own port....")
    s.listen()
    conn, addr = s.accept()
    message = conn.recv(1024).decode()
    if message == "Request to add host to the log!":
        conn.send(bytes("Request granted! Send host name!", "utf-8"))
        name = conn.recv(1024).decode()
        conn.send(bytes("Send address!", "utf-8"))
        address = conn.recv(1024).decode()
        log[name] = address
        conn.close()
        s.close()
        print("The server log now:")
        print(log)
        print("BGP Server still running!")

    else:
        conn.send(bytes("Request granted! Send host name!", "utf-8"))
        name = conn.recv(1024).decode()
        conn.send(bytes("Send data to be transferred!", "utf-8"))
        data = conn.recv(1024).decode()
        conn.close()
        s.close()
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        addr = log[name]
        s.connect((HOST, int(addr[13:-2])))
        s.send(bytes("Requesting data transfer by "+name, "utf-8"))
        message = s.recv(1024).decode()
        print("Message received: "+message)
        s.send(bytes(data , "utf-8"))
        s.close()
        print("BGP Server still running!")