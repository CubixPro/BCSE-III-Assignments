import multiprocessing
import threading
import random
import time
import helper
from createPacket import *
import const

class Channel:
    def __init__(self, senderToChannel, channelToSender, receiverToChannel, channelToReceiver):  
        
        self.senderToChannel    = senderToChannel
        self.channelToSender    = channelToSender 
        self.receiverToChannel  = receiverToChannel
        self.channelToReceiver  = channelToReceiver
        self.working            = False

    def channelizePktFromSenderToReceiver(self):

        while True:   
            packet = self.senderToChannel.recv()
            self.working = True 
            time.sleep(const.PropagationTime)
            self.working = False
            receiver = packet.decodeDestAddress()
            self.channelToReceiver[receiver].send(packet)

    def sendSignalToSender(self, sender):

        while True:
            if(self.working):
                self.channelToSender[sender].send(str(1)) #busy
            else:
                self.channelToSender[sender].send(str(0)) #idle

    def startChannel(self):
        
        print("\nCHANNEL is running")
        channelToReceiverThreadList = []
        channelToSenderThreadList = []
        sender = 0

        t = threading.Thread(name= 'PktThread'+str(sender+1), target=self.channelizePktFromSenderToReceiver)
        channelToReceiverThreadList.append(t)
        for i in range(const.totalSenderNumber):
           
            s = threading.Thread(name= 'SignalThread'+str(sender+1), target=self.sendSignalToSender, args=(sender,))

            channelToSenderThreadList.append(s)
            sender += 1

        for thread in channelToReceiverThreadList:
            thread.start()

        for thread in channelToSenderThreadList:
            thread.start()

        for thread in channelToReceiverThreadList:
            thread.join()

        for thread in channelToSenderThreadList:
            thread.join()