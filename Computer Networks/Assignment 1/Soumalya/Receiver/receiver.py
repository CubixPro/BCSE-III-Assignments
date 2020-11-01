import socket
import decode
from colorama import Fore,Style
from time import sleep
receiver = socket.socket()
receiver.bind(('localhost', 5000))
receiver.listen(1)
print(Fore.CYAN+"Receiver is listenting...")
Style.RESET_ALL

while True:
    sender, addr = receiver.accept()
    print(Fore.GREEN+"Connection created!")
    Style.RESET_ALL
    method = sender.recv(1024).decode()
    method = method.lower()
    filename = sender.recv(1024).decode()
    print("Output file accepted!")
    success = 0
    print("Decoding output file with {} method!".format(method))
    if method.lower() == 'vrc': success = decode.VRC(filename)
    elif method.lower() == 'checksum': success = decode.CHECKSUM(filename)
    elif method.lower() == 'lrc': success = decode.LRC(filename)
    elif method.lower() == 'crc': success = decode.CRC(filename, "1001")

    if not success: 
        sender.send(bytes("Faliure",'utf-8'))
        sleep(0.2)
        sender.send(bytes("Corrupted File received!\nRequest for retransmission!",'utf-8'))
    else: 
        sender.send(bytes("success",'utf-8'))
        sleep(0.2)
        sender.send(bytes("No error detected!\nFile received successfully!",'utf-8'))

    print(Fore.MAGENTA+ "****************************")
    print(Fore.CYAN+"Receiver is still listenting...")
    Style.RESET_ALL
    
