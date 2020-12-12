import multiprocessing
import threading
import sys
import random
import time
sys.path.append('../package')
import helper
from packet import *
import const

class PktDispatcher:
    def __init__(self, name, channelToDispatcher, dispatcherToChannel, dispatcherToReceiver, receiverToDispatcher):

        self.name = name
        self.channelToDispatcher    = channelToDispatcher
        self.dispatcherToChannel    = dispatcherToChannel
        self.dispatcherToReceiver   = dispatcherToReceiver # needs to be a list of pipes writeheads
        self.receiverToDispatcher   = receiverToDispatcher
    
    def dispatchPktToReceiver(self):
        while True:
            packet = self.channelToDispatcher.recv()
            receiver = packet.dest
            print("(Dispatcher:) sending packet to receiver{}".format(receiver))
            self.dispatcherToReceiver[receiver].send(packet)
    
    def dispatchACKFromReceiverToChannel(self, receiver): # needs to run for every receiver
        while True:
            print("(PktDispatcher:) Receiving...")
            ack = self.receiverToDispatcher[receiver].recv()
            self.dispatcherToChannel.send(ack)
            print("(PktDispatcher:) ACK sent to channel!")
    
    def startDispatcher(self):
        receiver = 0
        receiverToDispatcherThreadList = []

        for _ in range(const.totalReceiverNumber):
            t = threading.Thread(name='ackReceiveThread'+str(receiver+1),
                                    target=self.dispatchACKFromReceiverToChannel,
                                    args=(receiver,)
                                    )
            receiver += 1
            receiverToDispatcherThreadList.append(t)
        
        toReceiverThread = threading.Thread(name='toReceiver', 
                                                target=self.dispatchPktToReceiver
                                                )

        
        ###################################
        # start and join the threads
        ###################################

        for thread in receiverToDispatcherThreadList:
            thread.start()
        
        toReceiverThread.start()

        toReceiverThread.join()
        for thread in receiverToDispatcherThreadList:
            thread.join()

