import helper

class Packet:

    def __init__(self, _type, seqNo, segmentData, sender,dest):
        self.type = _type 
        self.segmentData = segmentData
        self.sender = sender
        self.dest = dest
        self.seqNo = seqNo

    #  preamble + sfd + dest + source + seqNo +len + data + cksum
    #     7     +  1  +  6   +   6    +  1    +  1 +  46  +   4  =  72

    def makePacket(self):
        preamble = '01'*28 
        sfd = '10101011' 
        seqToBits = '{0:08b}'.format(int(self.seqNo))
        destAddress = '{0:048b}'.format(int(self.dest))
        length = '{0:008b}'.format(len(self.segmentData))
        sourceAddress = '{0:048b}'.format(int(self.sender))
        data = ""
        for i in range(0, len(self.segmentData)):
            character = self.segmentData[i]
            dataByte = '{0:08b}'.format(ord(character))
            data = data + dataByte
        # print(data)
        packet = preamble + sfd + destAddress + sourceAddress + seqToBits + length + data    
        ckSum = helper.checkSum(packet)
        packet = packet + ckSum
        # print(len(packet))
        self.packet = packet
        return self

    def __str__(self):
        return str(self.packet)
    
    def extractData(self):
        text = ""
        data = self.packet[176:544]
        asciiData = [data[i:i+8] for i in range(0,len(data),8)]
        for letter in asciiData:
            text += chr(int(letter,2))
        return text

    def decodeLength(self):
        return len(self.segmentData)

    def decodeDestAddress(self):
        dest = self.packet[64:112]
        destAddress = int(dest,2)
        return destAddress
    
    def decodeSourceAddress(self):
        source = self.packet[112:160]
        sourceAddress = int(source,2)
        return sourceAddress
    
    def checkForError(self):
        return helper.checkError(self.packet)

    def checkType(self):
        return self.type

    def decodeSeqNo(self):
        seqNo = self.packet[160:168]
        return int(seqNo,2)