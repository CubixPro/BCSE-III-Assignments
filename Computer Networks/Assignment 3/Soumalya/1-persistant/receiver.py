import multiprocessing
import sys
import time
sys.path.append('../package')
import helper
import const
from packet import *

"""
receiverToPktDispatcher, pktDispatcherToReceiver -> needs to be pipes
endTransmission is true of false depending on the status of the system

"""

class Receiver:
    def __init__(self, name, receiverToPktDispatcher, pktDispatcherToReceiver, endTransmission):
        self.name                       = name
        self.seqNo                      = dict() # need to be sync with sender
        self.packetType                 = {'data' : 0, 'ack' : 1}
        #self.channelEvent              = channelEvent
        self.senderList                 = dict()
        self.receiverToPktDispatcher    = receiverToPktDispatcher #write
        self.pktDispatcherToReceiver    = pktDispatcherToReceiver #read
        self.endTransmission            = endTransmission


    def sendAck(self, sender, seqNo):
        packet = Packet(_type=self.packetType['ack'],
                        seqNo=seqNo,
                        segmentData='acknowledgement Packet',
                        sender=self.name,
                        dest=sender).makePacket()
        
        self.recentACK = packet
        self.receiverToPktDispatcher.send(packet)
    
    def resendPreviousACK(self,sender, seqNo):
        packet = Packet(_type=self.packetType['ack'],
                        seqNo=(seqNo),
                        segmentData='acknowledgement Packet',
                        sender=self.name,
                        dest=sender).makePacket()
        self.receiverToPktDispatcher.send(packet)
        print("Resending seq Number: {}".format(packet.seqNo))


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
        #time.sleep(0.4)
        while True:
            #print("**************************************************")
            print("(Receiver{}:) Receiving...".format(self.name+1))
            #print("**************************************************")
            #print("**************************************************")
            packet = self.pktDispatcherToReceiver.recv()
            print("(Receiver{}:) PACKET RECEIVED!!".format(self.name+1))
            # check for error
            if packet.checkForError():
                print("(Receiver{}:) ERROR CHECKED!!".format(self.name+1))
                sender = self.decodeSender(packet)
                seqNo = self.decodeSeqNo(packet)
                #print("Seq no at receiver: {}".format(seqNo))
                if self.seqNo.get(sender,0) == seqNo:
                    if sender not in self.senderList.keys():
                        self.senderList[sender] = const.outFilePath + 'output' + str(sender)
                        self.seqNo[sender] = 0 #initialising sender seqNo with 0
                

                    # file already added to the dict
                    outFile = self.senderList[sender]
                    file = self.openFile(outFile)
                    data = packet.extractData()
                    file.write(data)
                    file.close()
                    self.seqNo[sender] = (self.seqNo[sender]+1)%2
                    #print("at receiver seqNo dispatched: {}".format(self.seqNo[sender]))
                    self.sendAck(sender,self.seqNo[sender])
                    print("(Receiver{}:) ACK SENT FROM RECEIVER TO DISPATCHER!!".format(self.name+1))
                else:
                    self.resendPreviousACK(sender,self.seqNo[sender])
                    # print("(Receiver{}:) Sequence No matched!!".format(self.name+1))
                    print("(Receiver{}:) ACK RESENDED!".format(self.name+1))
            else:
                self.discardPacket()
                print("(Receiver{}:) PACKET DISCARDED2!!".format(self.name+1))
            
            if self.endTransmission: break
