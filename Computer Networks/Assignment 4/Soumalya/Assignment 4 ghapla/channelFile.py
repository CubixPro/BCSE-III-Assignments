import multiprocessing
import random
import time
import threading
import sys
import const

class Channel:
    def __init__(self, name, senderToChannel, channelToReceiver):
        self.name                   = name
        self.senderToChannel        = senderToChannel
        self.channelToReceiver      = channelToReceiver
        


    def takeDataFromSenderAndDistribute(self):
        while True:
            data = []
            data = self.senderToChannel.recv()
            for i in range(const.totalReceiverNumber):
                self.channelToReceiver[i].send(data)
            
    

    def startChannel(self):
        t = threading.Thread(name="channel", target=self.takeDataFromSenderAndDistribute)
        t.start()
        t.join()


