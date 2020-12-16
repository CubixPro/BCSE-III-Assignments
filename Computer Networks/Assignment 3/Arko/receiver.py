import multiprocessing
import time
import helper
import const
import sys
from createPacket import *

class Receiver:
    def __init__(self, name, channelToReceiver):
        self.name               = name
        self.packetType         = {'data' : 0, 'ack' : 1}
        self.senderList         = dict()
        self.channelToReceiver  = channelToReceiver 
        self.seqNo              = 0
        self.recentACK          = Packet(1, 0, "Acknowledgement Packet", self.name, 0).makePacket()

    def openFile(self, filepath):
        try:
            file = open(filepath, 'a+')
        except IOError:
            sys.exit("File path not exit!")
        return file

    def decodeSender(self,packet):
        senderAddress = packet.decodeSourceAddress()
        return senderAddress
  
    def startReceiving(self):
        while True:
            packet = self.channelToReceiver.recv()
            sender = self.decodeSender(packet)

            if sender not in self.senderList.keys():
                self.senderList[sender] = const.outFilePath + 'output' + str(sender)
                
            outFile = self.senderList[sender]
            file = self.openFile(outFile)
            data = packet.extractData()
            file.write(data)
            file.close()
            print("RECEIVER{} -->> PACKET RECEIVED".format(self.name+1))