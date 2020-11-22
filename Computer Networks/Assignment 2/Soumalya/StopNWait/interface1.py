import multiprocessing
import threading
import sys
import random
import time
from sender import Sender
sys.path.append('../package')
import helper
from packet import *
import const

ack = Packet(1,1,"ja bara",0,0).makePacket()

def check(readHead, writeHead):
    p = readHead.recv()
    print(p)
    writeHead.send(ack)
    print("send!")


def start():

    #check(readHead1,writeHead2)
    readHead1, writeHead1 = multiprocessing.Pipe()
    readHead2, writeHead2 = multiprocessing.Pipe()
    sender = Sender(0,'input0.txt',writeHead1,readHead2)
    
    p1 = threading.Thread(target=sender.transmit)
    p2 = threading.Thread(target=check, args=(readHead1,writeHead2))

    p2.start()
    p1.start()
    p1.join()
    p2.join()

if __name__ == "__main__":
    start()