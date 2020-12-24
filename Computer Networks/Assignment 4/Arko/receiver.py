import multiprocessing
import random
import time
import threading
import sys
import const


class Receiver:
    def __init__(self, name, walshTable, channelToReceiver):
        self.name               = name
        self.walshTable         = walshTable
        self.channelToReceiver  = channelToReceiver
        self.senderToReceive    = self.selectSender()
        self.codeLength         = len(self.walshTable[0])

    def selectSender(self):
        return self.name
  
    def getCharacter(self, data):
        print("Data:" + str(data))
        sum = 0
        for i in range(8):
            sum += pow(2,i)*data[7-i]
        #print(sum)
        character = chr(sum)
        print("Char received: " + character)
        return character
    
    def openFile(self, sender):
        try:
            file = open(const.outFilePath+'output'+str(sender+1)+'.txt', 'a+')
        except IOError:
            sys.exit("File path not exit!")

        return file
    
    def receiveData(self):
        print("(Receiver{}:) Receiver{} receives data from sender{}".format(self.name+1,self.name+1,self.senderToReceive+1))
        totalData = []
        while True:
            channelData = self.channelToReceiver.recv()
            # extract data
            summation = 0
            for i in range(len(channelData)):
                summation += channelData[i] * self.walshTable[self.senderToReceive][i]
            
            # extract data bit
            summation /= self.codeLength
            if summation == 1:
                bit = 1
            elif summation == -1:
                bit = 0
            else: bit = -1
            
            print("(Receiver{}:) Bit received: {}".format(self.name+1, bit))

            if len(totalData) < 8 and bit != -1:
                #print("Receiver{} -->> Lenght of totalData {}".format(self.name+1, len(totalData)))
                totalData.append(bit)

            if(len(totalData) == 8):
                character = self.getCharacter(totalData)
                outFile = self.openFile(self.senderToReceive)
                outFile.write(character)
                outFile.close()
                totalData = []
                

    def startReceiver(self):
        t = threading.Thread(name='Receiver', target=self.receiveData)
        t.start()
        t.join()