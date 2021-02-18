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
        self.start              = 0

    def selectReceiver(self):
        return random.randint(0, const.totalReceiverNumber-1)

    def openFile(self, filename):
        try:
            file = open(filename, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(filename))
        
        return file

    def resendCurrentPacket(self):
        self.senderToChannel.send(self.recentPacket)

    def dataIntoFrames(self):

        time.sleep(0.2)
        print("SENDER{} starts sending data to RECEIVER{}\n".format(self.name+1, self.dest+1))
        file = self.openFile(self.fileName)

        byte = file.read(const.defaultDataPacketSize)
        self.seqNo = 0
        pktCount = 0
        totalPktCount = 0
        while byte:
            packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
            self.recentPacket = packet
            self.senderToChannel.send(packet)
            self.seqNo = (self.seqNo+1)%2
            pktCount += 1
            totalPktCount += 1
            print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, pktCount))
            while True:
                self.timeoutEvent.wait(const.senderTimeout)
                time.sleep(0.2)
                if not self.timeoutEvent.isSet(): 
                    self.resendCurrentPacket()
                    totalPktCount += 1
                    print("SENDER{} -->> PACKET {} HAS BEEN RESENDING".format(self.name+1, pktCount))
                else: break
            self.timeoutEvent.clear()

            byte = file.read(const.defaultDataPacketSize)
            if len(byte) == 0: break
            elif len(byte) < const.defaultDataPacketSize: 
                tempLength = len(byte)
                for char in range(const.defaultDataPacketSize - tempLength):
                    byte += '\0'
        
        self.endTransmitting = True
        file.close()

        print("\n*****************SENDER{} -->> STATS******************".format(self.name+1))
        print("Total packets: {}\nTotal Packets send {}".format(pktCount, totalPktCount))
        print("Time Taken till now: ", round((time.time() - self.start)/60, 2), " mins\n")
        

    def checkAckPackets(self):
        time.sleep(0.2)
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