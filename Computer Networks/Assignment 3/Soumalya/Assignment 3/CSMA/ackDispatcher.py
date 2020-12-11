import multiprocessing
import threading
import sys
import random
import time
sys.path.append('../package')
import helper
from packet import *
import const

class ackDispatcher:
    def __init__(self, name, channelToDispatcher, dispatcherToSender):
        self.name                   = name
        self.channelToDispatcher    = channelToDispatcher
        self.dispatcherToSender     = dispatcherToSender
    
    def sendACKToSender(self):
        while True:
            ack = self.channelToDispatcher.recv()
            sender = ack.dest
            self.dispatcherToSender[sender].send()
    
    def startDispatcher(self):
        thread = threading.Thread(name='ackDispatcher', target=self.sendACKToSender)
        thread.start()
        thread.join()