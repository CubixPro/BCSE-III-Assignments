#!/usr/bin/env python3

import socket


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65000        # Port to listen on (non-privileged ports are > 1023)

print("Server started!!")

Dict = {}
while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    print("Listening for a connection on its own port....")
    s.listen()
    conn, addr = s.accept()
    print("Connection successful!")
    conn.send(bytes("Send client status!", "utf-8"))
    status = conn.recv(1024).decode()
    conn.send(bytes("Send client name!", "utf-8"))
    name = conn.recv(1024).decode()
    try:
        Dict[name] = Dict[name]
    except KeyError:
        Dict[name] = {}
    while True:
        conn.send(bytes("Send command!", "utf-8"))
        comm = conn.recv(1024).decode()
        if comm == "put":
            conn.send(bytes("Send key!", "utf-8"))
            key = conn.recv(1024).decode()
            conn.send(bytes("Send value!", "utf-8"))
            value = conn.recv(1024).decode()
            Dict[name][key] = value
            print(Dict)
        elif comm == "get":
            conn.send(bytes("Send key!", "utf-8"))
            key = conn.recv(1024).decode()
            try:
                value = Dict[name][key]
            except KeyError:
                value = " "
            conn.send(bytes(value, "utf-8"))
        else:
            break

    conn.close()
    print("Server still running!")