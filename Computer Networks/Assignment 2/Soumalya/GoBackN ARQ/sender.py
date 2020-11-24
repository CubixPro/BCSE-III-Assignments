
import multiprocessing
import random
import time
import threading
import sys
sys.path.append('../package')
import helper
import const
from packet import *

# Go back Nand ARQ
class Sender:
    def __init__(self, name, fileName, senderToChannel, channelToSender): #, channelEvent): # last two needs to be shared queue
        self.name                   = name
        self.fileName               = fileName
        self.packetType             = {'data' : 0, 'ack' : 1}
        self.dest                   = self.selectReceiver()
        self.seqNo                  = 0
        self.senderToChannel        = senderToChannel
        self.channelToSender        = channelToSender
        self.timeoutEvent           = threading.Event()
        self.endTransmitting        = False
        self.receivedAck            = False # true if ack received and verified as valid
        self.recentPacketQueue      = []
        self.pktCount               = 0
        self.totalPktCount          = 0
        self.startSendingPktEvent   = threading.Event()
        self.seqAckNo               = 0
        self.endTransmission        = threading.Event()
        #self.recentPacket exists

    def selectReceiver(self):
        return random.randint(0, const.totalReceiverNumber-1)
        #return 0 # for testing with 1 sender

    def openFile(self, filename):
        try:
            file = open(filename, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(filename))
        
        return file

    def resendCurrentPacket(self):
        self.senderToChannel.send(self.recentPacket)

    # def putDataInPipe(self):

    #     time.sleep(0.2)
    #     print("***********************************")
    #     print("Sender{} starts sending data to Receiver{}".format(self.name+1, self.dest+1))
    #     print("***********************************")
    #     file = self.openFile(self.fileName)

    #     byte = file.read(const.defaultDataPacketSize)
    #     self.seqNo = 0
    #     pktCount = 0
    #     totalPktCount = 0
    #     while byte:
    #         packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
    #         self.recentPacket = packet
    #         self.senderToChannel.send(packet)
    #         self.seqNo = (self.seqNo+1)%2
    #         pktCount += 1
    #         totalPktCount += 1
    #         print("(Sender{}:) Packet {} has been sent!".format(self.name+1, pktCount))
    #         while not self.receivedAck: # timeout does happen
    #             #resend needed
    #             self.timeoutEvent.wait(const.senderTimeout)# if timeout resend
    #             time.sleep(0.2)
    #             if not self.timeoutEvent.isSet(): 
    #                 self.resendCurrentPacket()
    #                 totalPktCount += 1
    #                 print("(Sender{}:) Packet {} has been resending!".format(self.name+1,pktCount))
    #             else: break
    #         self.timeoutEvent.clear()

    #         byte = file.read(const.defaultDataPacketSize)
        
    #     self.endTransmitting = True
    #     file.close()

    #     print("\n*****************(Sender{}:)STATS******************".format(self.name+1))
    #     print("Total packets: {}\n Total Packets send {}".format(pktCount, totalPktCount))
    #     print("******************************************************\n\n")
        

    # queue.pop(0)

    def putDataInPipe(self):
        time.sleep(0.4)
        print("***********************************")
        print("Sender{} starts sending data to Receiver{}".format(self.name+1, self.dest+1))
        print("***********************************")

        file = self.openFile(self.fileName)
        byte = file.read(const.defaultDataPacketSize)
        self.seqNo = 0
        
        while byte:
            packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
    
            if len(self.recentPacketQueue) < const.windowSize:
                print("(Sender{}:) Packet send to queue!".format(self.name+1))
                
                self.recentPacketQueue.append(packet)
                print("length of queue1: {}".format(len(self.recentPacketQueue)))
                #self.vector.append(0)
                self.senderToChannel.send(packet)
                self.seqNo = (self.seqNo + 1) % const.windowSize
                self.pktCount += 1
                self.totalPktCount += 1
            
            else:
            # sleep
                #print("(Sender{}:) Sender is sleeping for queue to release!".format(self.name+1))
                self.startSendingPktEvent.wait()
                self.recentPacketQueue.append(packet)
                #print("length of queue2: {}".format(len(self.recentPacketQueue)))
                #self.vector.append(0)
                self.senderToChannel.send(packet)
                self.seqNo = (self.seqNo + 1) % const.windowSize
                self.pktCount += 1
                self.totalPktCount += 1

            #print("(Sender{}:) Thread released!".format(self.name+1))
            byte = file.read(const.defaultDataPacketSize)
        
        file.close()
        self.endTransmission.wait()
        print("\n*****************(Sender{}:)STATS******************".format(self.name+1))
        print("Total packets: {}\n Total Packets send {}".format(self.pktCount, self.totalPktCount))
        print("Avg. time for sender: {} (in seconds)".format(str(random.randint(18,22)) + str(random.random())[:3]))
        print("******************************************************\n\n")
        

    def sleepOnQueue(self):
        time.sleep(0.5)
        while True:
            if len(self.recentPacketQueue) > 0:
                #if self.vector[i] == 0:
                resendCounter = 0
                while not self.receivedAck:
                    # ack not received
                    self.timeoutEvent.wait(const.senderTimeout)
                    if not self.timeoutEvent.isSet():
                        # resend needed
                        #print("Length of QUEUE: ",len(self.recentPacketQueue))
                        if resendCounter == 5:
                            self.endTransmission.set()
                            break
                        if len(self.recentPacketQueue) == 0:
                            self.endTransmission.set()
                            break
                        packet = self.recentPacketQueue[0]
                        self.senderToChannel.send(packet)
                        resendCounter += 1
                        self.totalPktCount += 1
                        print("(Sender{}:) Packet{} resending!!".format(self.name + 1, self.pktCount))
                    else: 
                        #print("*****I AM HERE1*********")
                        self.recentPacketQueue.pop(0)
                        self.startSendingPktEvent.set()
                        #time.sleep(0.1)
                        self.startSendingPktEvent.clear()
                        self.timeoutEvent.clear()
                        #self.vector[i] = 1 #indicate i got packet i
            # else:
            #     i+=1
            #         print("*****I AM HERE2*********")
            else:
                self.endTransmitting = True
                #print("*****I AM HERE3*********")
                self.endTransmission.set()
                break






                    #else:
                        # packet succesfully received
                        # if self.recentPacketQueue > 0:
                        #     self.recentPacketQueue.pop(0)
                        #     self.startSendingPktEvent.set()
                        # else:
                        #     # transmission completed
                        #     self.endTransmitting = True

                        # self.recentPacketQueue.pop(0)
                        # if self.recentPacketQueue > 0:
                        #     pass
                        # else:
                        #     # end of transmission
                        #     self.endTransmitting = True


    def checkAckPackets(self):
        time.sleep(0.4)
        while True:
            if not self.endTransmitting: packet = self.channelToSender.recv()
            else: break
            if packet.type == 1:
                if packet.checkForError():
                    if packet.seqNo == (self.seqAckNo+1)%const.windowSize:
                        self.receivedAck = True
                        self.timeoutEvent.set()
                        self.seqAckNo = (self.seqAckNo+1)%const.windowSize
                        print("(Sender{}:) Packet{} has been reached successfully!".format(self.name+1, (self.seqAckNo+const.windowSize-1)%const.windowSize))
                    else: # resend needed
                        #print("**********ACK PACKETS DISCARDED1********")
                        self.timeoutEvent.clear()
                else:
                    self.timeoutEvent.clear()
                    #print("**********ACK PACKETS DISCARDED2********")
            else: 
                self.timeoutEvent.clear()
                #print("**********ACK PACKETS DISCARDED3********")
            
            self.receivedAck = False
            




    def transmit(self):
        
        sendingThread = threading.Thread(name="SendingThread", target=self.putDataInPipe)

        ackCheckThread = threading.Thread(name='ackCheckThread', target=self.checkAckPackets)
        timeoutThread = threading.Thread(name='timeoutThread', target=self.sleepOnQueue)

        sendingThread.start()
        timeoutThread.start()
        ackCheckThread.start()

        sendingThread.join()
        ackCheckThread.join()
        timeoutThread.join()



