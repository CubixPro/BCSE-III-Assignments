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
    def __init__(self, name, senderToChannel, channelToSender, receiverToChannel, channelToReceiver):  #, senderEventList, receiverEventList):
        
        self.name               = name
        self.senderToChannel    = senderToChannel
        self.channelToSender    = channelToSender # these need to be pipe list of exact size of no of sender or no of receiver
        self.receiverToChannel  = receiverToChannel
        self.channelToReceiver  = channelToReceiver


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
    def channelizePktFromSenderToReceiver(self,sender):# sender = 0,1,2..sender address basically
        time.sleep(0.5)
        while True:    
            print("(Channel:) channel is receiving...")
            packet = self.senderToChannel[sender].recv()
            receiver = packet.decodeDestAddress()
            if random.random() <= const.dropOutProb:
                # dropout the packet
                print("(Channel:) PACKET DROPPED OUT!")
                self.fakeFunction()
            else:
                if random.random() <= const.injectErrorProb:
                    print("(Channel:) INJECTING ERROR!")
                    self.injectError(packet)

                if random.random() <= const.delayProb:
                    print("(Channel:) INTRODUCING DELAY")                        
                    time.sleep(const.delay)
                    
                self.channelToReceiver[receiver].send(packet)

    # needed a thread to run this for every sender
    def channelizeACKFromReceiverToSender(self, receiver): # receiver can be 0,1,2..
        time.sleep(0.5)
        while True:
            print("(Channel:) Channel is receiving...")
            ack = self.receiverToChannel[receiver].recv()
            sender = ack.decodeDestAddress()
            if random.random() <= const.dropOutProb:
                # dropout the packet
                print("(Channel:) ACK PACKET DROPPED OUT!")
                self.fakeFunction()
            else:
                if random.random() <= const.injectErrorProb:
                   print("(Channel:) ACK INJECTING ERROR!")
                   self.injectError(ack)
                if random.random() <= const.delayProb:
                    print("(Channel:) ACK INTRODUCING DELAY")
                    time.sleep(const.delay)
    
                self.channelToSender[sender].send(ack)

    def startChannel(self):

        senderToReceiverThreadList = []
        receiverToSenderThreadList = []
        sender = 0
        receiver = 0
        for _ in range(const.totalSenderNumber):
            t = threading.Thread(name= 'PktThread'+str(sender+1), 
                                        target=self.channelizePktFromSenderToReceiver,
                                            args=(sender,))
            senderToReceiverThreadList.append(t)
            sender += 1
            
        for _ in range(const.totalReceiverNumber):
            t = threading.Thread(name= 'ACKThread'+str(receiver+1), 
                                        target=self.channelizeACKFromReceiverToSender, 
                                            args=(receiver,))
            receiverToSenderThreadList.append(t)
            receiver += 1

        for thread in senderToReceiverThreadList:
            thread.start()
            
        for thread in receiverToSenderThreadList:
            thread.start()

        for thread in senderToReceiverThreadList:
            thread.join()
            
        for thread in receiverToSenderThreadList:
            thread.join()

            

