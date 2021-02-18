import multiprocessing
import time
import helper
import const
import sys
from createPacket import *

class Receiver:
    def __init__(self, name, receiverToChannel, channelToReceiver):
        self.name               = name
        self.packetType         = {'data' : 0, 'ack' : 1}
        self.senderList         = dict()
        self.receiverToChannel  = receiverToChannel #write
        self.channelToReceiver  = channelToReceiver #read
        self.seqNo              = 0
        self.recentACK          = Packet(1, 0, "Acknowledgement Packet", self.name, 0).makePacket()

    def sendAck(self, sender, seqNo):
        packet = Packet(_type=self.packetType['ack'],
                        seqNo=self.seqNo,
                        segmentData='acknowledgement Packet',
                        sender=self.name,
                        dest=sender).makePacket()
        
        self.recentACK = packet
        self.receiverToChannel.send(packet)
    
    def resendPreviousACK(self):
        self.receiverToChannel.send(self.recentACK)

    def openFile(self, filepath):
        try:
            file = open(filepath, 'a+')
        except IOError:
            sys.exit("File path not exit!")
        return file

    def decodeSeqNo(self, packet):
        return packet.decodeSeqNo()

    def decodeSender(self,packet):
        senderAddress = packet.decodeSourceAddress()
        return senderAddress
  
    def startReceiving(self):
        time.sleep(0.4)
        while True:
            packet = self.channelToReceiver.recv()
            print("RECEIVER{} -->> PACKET RECEIVED".format(self.name+1))
            
            if packet.checkForError():
                print("RECEIVER{} -->> ERROR CHECKED".format(self.name+1))
                sender = self.decodeSender(packet)
                seqNo = self.decodeSeqNo(packet)
                if self.seqNo == seqNo:
                    if sender not in self.senderList.keys():
                        self.senderList[sender] = const.outFilePath + 'output' + str(sender)
                    outFile = self.senderList[sender]
                    file = self.openFile(outFile)
                    data = packet.extractData()
                    file.write(data)
                    file.close()
                    self.seqNo = (self.seqNo+1) % const.windowSize
                    self.sendAck(sender,self.seqNo)
                    print("RECEIVER{} -->> ACK SENT FROM RECEIVER".format(self.name+1))
                else:
                    self.resendPreviousACK()
                    print("RECEIVER{} -->> ACK RESENDED".format(self.name+1))
            else:
                print("RECEIVER{} -->> PACKET DISCARDED".format(self.name+1))