import multiprocessing
import sys
import time
sys.path.append('../package')
import helper
import const
from packet import *

"""
receiverToChannel, channelToReceiver -> needs to be pipes
channelEvent = need to be shared with receiver and channel
endTransmission is true of false depending on the status of the system


"""

class Receiver:
    def __init__(self, name, receiverToChannel, channelToReceiver, endTransmission):
        self.name               = name
        self.seqNo              = 0 # need to be sync with sender
        self.packetType         = {'data' : 0, 'ack' : 1}
        #self.channelEvent       = channelEvent
        self.senderList         = dict()
        self.receiverToChannel  = receiverToChannel #write
        self.channelToReceiver  = channelToReceiver #read
        self.endTransmission    = endTransmission


    def sendAck(self, sender, seqNo):
        packet = Packet(_type=self.packetType['ack'],
                        seqNo=seqNo,
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

    def decodeSender(self,packet):
        senderAddress = packet.decodeSourceAddress()
        return senderAddress
    
    def decodeSeqNo(self, packet):
        return packet.decodeSeqNo()

    def discardPacket(self):
        return 0

  
    def startReceiving(self):
        time.sleep(0.4)
        while True:
            #print("**************************************************")
            print("(Receiver{}:) Receiving...".format(self.name+1))
            #print("**************************************************")
            #print("**************************************************")
            packet = self.channelToReceiver.recv()
            print("(Receiver{}:) PACKET RECEIVED!!".format(self.name+1))
            # check for error
            if packet.checkForError():
                print("(Receiver{}:) ERROR CHECKED!!".format(self.name+1))
                sender = self.decodeSender(packet)
                seqNo = self.decodeSeqNo(packet)
                if self.seqNo == seqNo:
                    if sender not in self.senderList.keys():
                        self.senderList[sender] = const.outFilePath + 'output' + str(sender)
                

                    # file already added to the dict
                    outFile = self.senderList[sender]
                    file = self.openFile(outFile)
                    data = packet.extractData()
                    file.write(data)
                    file.close()
                    self.seqNo = (self.seqNo+1)%2
                    self.sendAck(sender,self.seqNo)
                    print("(Receiver{}:) ACK SENT FROM RECEIVER!!".format(self.name+1))
                else:
                    self.resendPreviousACK()
                    # print("(Receiver{}:) Sequence No matched!!".format(self.name+1))
                    print("(Receiver{}:) ACK RESENDED!".format(self.name+1))
            else:
                self.discardPacket()
                print("(Receiver{}:) PACKET DISCARDED2!!".format(self.name+1))
            
            if self.endTransmission: break
