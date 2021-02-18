import multiprocessing
import random
import time
import threading
import sys
import const

class Channel:
    def __init__(self, name, senderToChannel, channelToReceiver):
        self.name               = name
        self.senderToChannel    = senderToChannel
        self.channelToReceiver  = channelToReceiver
        self.channelData        = [0 for i in range(const.totalSenderNumber)]  # channel data to be distributed
        self.syncValue          = 0
        


    def takeDataFromSenderAndDistribute(self):
        while True:

            for i in range(const.totalSenderNumber):
            
                data = []
                data = self.senderToChannel.recv()
                print("Channel...." + str(data))
              
                # update channel Data
                for i in range(len(data)):
                    self.channelData[i] += data[i] 
                
                self.syncValue += 1

                if self.syncValue == const.totalSenderNumber:   
                    # distribute over every receiver
                    for receiver in range(const.totalReceiverNumber):
                        self.channelToReceiver[receiver].send(self.channelData)
                    
                    # reset self.value and channelData for next bit transfer
                    self.syncValue = 0
                    self.channelData = [0 for i in range(len(data))]
            
    
    def startChannel(self):
        
        t = threading.Thread(name="channel", target=self.takeDataFromSenderAndDistribute)
        t.start()
        t.join()
