import sys
sys.path.append('../package')
import helper

class Packet:

    def __init__(self, _type, seqNo, segmentData, sender,dest):
        self.type = _type # packet can be of type data, ack
        self.seqNo = seqNo
        self.segmentData = segmentData
        self.sender = sender
        self.dest = dest

# """
#  segment data need to be in string
#  byte = file.read(1)...segmentdata += str(byte)
#  everythong has to be in string
#  preamble + sfd + dest + source + seq + len + data + cksum
#   7       +  1  + 8    +   8    + 1   + 1   + 36   +  2 = 64
#   returns packet obj
# """
 ###############################
    def makePacket(self):
        preamble = '01'*28 # 7 bytes of alternating 01
        sfd = '10101011' # start frame delimeter
        seqToBits = '{0:08b}'.format(int(self.seqNo))
        destAddress = '{0:064b}'.format(int(self.dest))
        length = len(self.segmentData) #in bytes
        lenToBits = '{0:08b}'.format(length)
        sourceAddress = '{0:064b}'.format(int(self.sender))
        data = ""
        #print(len(self.segmentData))
        for i in range(0, len(self.segmentData)):
            character = self.segmentData[i]
            dataByte = '{0:08b}'.format(ord(character))
            data = data + dataByte
        
        packet = preamble + sfd + destAddress + sourceAddress + seqToBits + lenToBits + data    
        ckSum = helper.checkSum(packet)
        
        packet = packet + ckSum
        
        self.packet = packet
        return self

    def __str__(self):
        return str(self.packet)
    
    def extractData(self):
        text = ""
        data = self.packet[208:496]
        asciiData = [data[i:i+8] for i in range(0,len(data),8)]
        for letter in asciiData:
            text += chr(int(letter,2))
        return text
    
    def decodeLength(self):
        return len(self.segmentData)

    def decodeSeqNo(self):
        seqNo = self.packet[192:200]
        return int(seqNo,2)
    def decodeDestAddress(self):
        dest = self.packet[64:128]
        destAddress = int(dest,2)
        return destAddress
    
    def decodeSourceAddress(self):
        source = self.packet[128:192]
        sourceAddress = int(source,2)
        return sourceAddress
    
    def checkForError(self):
        return helper.checkError(self.packet)

    def checkType(self):
        return self.type