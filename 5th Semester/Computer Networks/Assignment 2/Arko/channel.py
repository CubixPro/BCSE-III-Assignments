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

    def injectError(self, packet):
        noOfErrors = random.randint(const.minError, const.maxError)
        listOFChar = list(packet.packet)
        length = packet.decodeLength()
        for i in range(noOfErrors):
            pos = random.randint(0,length-1)
            if listOFChar[pos] == '1': listOFChar[pos] = '0'
            else: listOFChar[pos] = '1'
            
        packet.packet = ''.join(listOFChar)

    def channelizePktFromSenderToReceiver(self,sender):
        time.sleep(0.5)
        while True:    
            packet = self.senderToChannel[sender].recv()
            receiver = packet.decodeDestAddress()
            if random.random() <= const.dropOutProb:
                print("CHANNEL -->> PACKET DROPPED OUT") # returns a float between (0,1)
            else:
                if random.random() <= const.injectErrorProb:
                    print("CHANNEL -->> INJECTING ERROR IN PACKET")
                    self.injectError(packet)

                if random.random() <= const.delayProb: 
                    print("CHANNEL -->> INTRODUCING DELAY IN PACKET")                        
                    time.sleep(const.delay)
                    
                self.channelToReceiver[receiver].send(packet)
                print("CHANNEL -->> PACKET SENT")

    def channelizeACKFromReceiverToSender(self, receiver): 
        time.sleep(0.5)
        while True:
            ack = self.receiverToChannel[receiver].recv()
            sender = ack.decodeDestAddress()
            if random.random() <= const.dropOutProb:
                print("CHANNEL -->> ACK DROPPED OUT")
            else:
                if random.random() <= const.injectErrorProb:
                    print("CHANNEL -->> INJECTING ERROR IN ACK")
                    self.injectError(ack)
                if random.random() <= const.delayProb:
                    print("CHANNEL -->> INTRODUCING DELAY IN ACK")
                    time.sleep(const.delay)
    
                self.channelToSender[sender].send(ack)
                print("CHANNEL -->> ACK SENT")

    def startChannel(self):

        senderToReceiverThreadList = []
        receiverToSenderThreadList = []
        sender = 0
        receiver = 0
        print("\nCHANNEL is running")
        for i in range(const.totalSenderNumber):
            t = threading.Thread(name= 'PktThread'+str(sender+1), 
                                        target=self.channelizePktFromSenderToReceiver,
                                            args=(sender,))
            senderToReceiverThreadList.append(t)
            sender += 1
            
        for i in range(const.totalReceiverNumber):
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