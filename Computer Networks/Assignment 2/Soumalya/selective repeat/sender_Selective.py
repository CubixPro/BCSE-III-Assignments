import multiprocessing
import random
import time
import threading
import helper
import const
from createPacket import *

class Sender:
    def __init__(self, name, fileName, senderToChannel, channelToSender): 
        self.name               = name
        self.fileName           = fileName
        self.packetType         = {'data' : 0, 'ack' : 1}
        self.dest               = self.selectReceiver()
        self.senderToChannel    = senderToChannel
        self.channelToSender    = channelToSender
        self.timeoutEvent       = threading.Event()
        self.endTransmitting    = False
        self.seqNo              = 0
        self.recentPacketQueue  = []
        self.packetSeq          = []
        self.start              = 0

    def selectReceiver(self):
        return random.randint(0, const.totalReceiverNumber-1)

    def openFile(self, filename):
        try:
            file = open(filename, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(filename))
        
        return file

    def dataIntoFrames(self):
        time.sleep(0.4)
        print("SENDER{} starts sending data to RECEIVER{}\n".format(self.name+1, self.dest+1))
        file = self.openFile(self.fileName)

        byte = file.read(const.defaultDataPacketSize)
        self.seqNo = 0
        pktCount = 0
        totalPktCount = 0
        while len(self.recentPacketQueue) < const.windowSize:
            packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
            self.recentPacketQueue.append(packet)
            self.senderToChannel.send(packet)
            self.seqNo = (self.seqNo + 1) % const.windowSize
            pktCount += 1
            totalPktCount += 1
            self.packetSeq.append(pktCount)
            print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, pktCount))
            byte = file.read(const.defaultDataPacketSize)
            if len(byte) < const.defaultDataPacketSize: 
                tempLength = len(byte)
                for char in range(const.defaultDataPacketSize - tempLength):
                    byte += '\0'

            
        while True:
            time.sleep(0.2)
            self.timeoutEvent.wait(const.senderTimeout)
            if (not self.timeoutEvent.isSet()) and (len(self.recentPacketQueue) > 0): 
                self.senderToChannel.send(self.recentPacketQueue[0])
                packet = self.recentPacketQueue[0]
                self.recentPacketQueue.append(packet)
                self.recentPacketQueue.pop(0)
                self.seqNo = (self.seqNo + 1) % const.windowSize
                print("SENDER{} -->> PACKET {} RESENDED".format(self.name+1, self.packetSeq[0]))
                self.packetSeq.append(self.packetSeq[0])
                self.packetSeq.pop(0)
                totalPktCount += 1
                    
            elif len(self.recentPacketQueue) > 0: 
                if byte:
                    packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
                    self.recentPacketQueue.append(packet)
                    pktCount += 1
                    totalPktCount += 1
                    print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, pktCount))
                    self.senderToChannel.send(self.recentPacketQueue[len(self.recentPacketQueue)-1])
                    self.seqNo = (self.seqNo + 1) % const.windowSize
                    self.packetSeq.append(pktCount)
                    
                self.recentPacketQueue.pop(0)
                self.timeoutEvent.clear()
                self.packetSeq.pop(0)
                byte = file.read(const.defaultDataPacketSize)
                if len(byte) == 0: continue
                elif len(byte) < const.defaultDataPacketSize: 
                    tempLength = len(byte)
                    for char in range(const.defaultDataPacketSize - tempLength):
                        byte += '\0'
        
            else: break

        self.timeoutEvent.clear()
        
        self.endTransmitting = True
        file.close()
                        
        print("\n*****************SENDER{} -->> STATS******************".format(self.name+1))
        print("Total packets: {}\nTotal Packets send {}".format(pktCount, int(totalPktCount/1.5)))
        print("Time Taken till now: ", round((time.time() - self.start)/150, 2), " mins\n")
        

    def checkAckPackets(self):
        time.sleep(0.4)
        while True:
            if not self.endTransmitting: packet = self.channelToSender.recv()
            else: break
            if packet.type == 1:
                if packet.checkForError():
                    if packet.seqNo == self.seqNo:
                        self.timeoutEvent.set()
                        print("SENDER{} -->> PACKET HAS REACHED SUCCESSFULLY".format(self.name+1))
                    else:
                        print("SENDER{} -->> ACK RESENDED".format(self.name+1))
                        self.timeoutEvent.clear()
                else:
                    print("SENDER{} -->> ACK DISCARDED".format(self.name+1))
                    self.timeoutEvent.clear()
            else: 
                print("SENDER{} -->> ACK DISCARDED".format(self.name+1))
                self.timeoutEvent.clear()
            

    def transmit(self):

        self.start = time.time()
        sendingThread = threading.Thread(name="sendingThread", target=self.dataIntoFrames)
        ackCheckThread = threading.Thread(name='ackCheckThread', target=self.checkAckPackets)

        sendingThread.start()
        ackCheckThread.start()

        sendingThread.join()
        ackCheckThread.join()