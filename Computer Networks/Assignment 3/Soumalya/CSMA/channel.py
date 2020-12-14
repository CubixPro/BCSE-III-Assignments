import multiprocessing
import threading
import sys
import random
import time
sys.path.append('../package')
import helper
from packet import *
import const

class Channel:
    def __init__(self, name, senderToChannel, channelToPktDispatcher, pktDispatcherToChannel, channelToACKDispatcher):  #, senderEventList, receiverEventList):
        
        self.name                       = name
        self.senderToChannel            = senderToChannel
        self.channelToPktDispatcher     = channelToPktDispatcher # these need to be pipe list of exact size of no of sender or no of receiver
        self.pktDispatcherToChannel     = pktDispatcherToChannel
        self.channelToACKDispatcher     = channelToACKDispatcher


    def fakeFunction(self):
        return 0

    def injectError(self, packet):
        noOfErrors = random.randint(10,100)
        listOFChar = list(packet.packet)
        length = packet.decodeLength()
        for _ in range(noOfErrors):
            pos = random.randint(0,length-1)
            if listOFChar[pos] == '1': listOFChar[pos] = '0'
            else: listOFChar[pos] = '1'
            
        packet.packet = ''.join(listOFChar)

    # needed a thread to run this for every sender
    def channelizePktFromSenderToDispatcher(self):# sender = 0,1,2..sender address basically
        while True:    
            print("(Channel:) channel is receiving...")
            packet = self.senderToChannel.recv()
            if random.random() <= const.dropOutProb:
                # dropout the packet
                print("(Channel:) PACKET DROPPED OUT!")
                self.fakeFunction()
                
            else:
                if random.random() <= const.injectErrorProb:
                    print("(Channel:) INJECTING ERROR!")
                    self.injectError(packet)
                    self.fakeFunction()

                if random.random() <= const.delayProb:
                    print("(Channel:) INTRODUCING DELAY")                        
                    time.sleep(const.delay)
                    
                self.channelToPktDispatcher.send(packet)

    # needed a thread to run this for every sender
    def channelizeACKFromDispatcherToSender(self): # receiver can be 0,1,2..
        #time.sleep(0.5)
        while True:
            print("(Channel:) Channel is receiving...")
            ack = self.pktDispatcherToChannel.recv()
            #sender = ack.decodeDestAddress()
            if random.random() <= const.dropOutProb:
                # dropout the packet
                print("(Channel:) ACK PACKET DROPPED OUT!")
                self.fakeFunction()

            else:
                if random.random() <= const.injectErrorProb:
                    #print("(Channel:) ACK INJECTING ERROR!")
                    #self.injectError(ack)
                    self.fakeFunction()
                if random.random() <= const.delayProb:
                    print("(Channel:) ACK INTRODUCING DELAY")
                    time.sleep(const.delay)
    
                self.channelToACKDispatcher.send(ack)

    def startChannel(self):

        thread1 = threading.Thread(name='SenderToDispatcher',
                                        target=self.channelizePktFromSenderToDispatcher
                                        )
        
        thread2 = threading.Thread(name='fromDispatcherToSender', 
                                        target=self.channelizeACKFromDispatcherToSender
                                        )

        thread1.start()
        thread2.start()

        thread1.join()
        thread2.join()

            

