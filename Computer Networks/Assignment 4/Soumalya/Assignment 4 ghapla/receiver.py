import multiprocessing
import random
import time
import threading
import sys
#sys.path.append('../package')
import const


class Receiver:
    def __init__(self, name, walshTable, channelToReceiver, waitTillReceived):
        self.name               = name
        self.walshTable         = walshTable
        self.channelToReceiver  = channelToReceiver
        self.waitTillReceived   = waitTillReceived
        self.senderToReceive    = self.selectSender()
        self.codeLength         = len(self.walshTable[0])

    def selectSender(self):
        num = random.randint(0, const.totalSenderNumber-1)
        return num

    def doNothing(self):
        return 0
    
    def getCharacter(self, data):
        print("Data:" + str(data))
        string = ''.join(data)
        character = chr(int(string,2))
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
            
            ########## extract databit#######
            summation /= self.codeLength
            if summation == 1:
                bit = 1
            elif summation == -1:
                bit = 0
            else: bit = -1
            ##################################
            print("(Receiver{}:) Bit received: {}".format(self.name+1, bit))

            if len(totalData) < 8 and bit != -1:
                # add the bit to totalData 
                totalData.append(str(bit))
            elif len(totalData) < 8 and bit == -1:
                self.doNothing()
            else:
                # totalData size is 8..we can construct a character now
                # write into a file

                character = self.getCharacter(totalData)
                outFile = self.openFile(self.senderToReceive)
                outFile.write(character)
                outFile.close()
                totalData = []
                
                if bit != -1:
                    totalData.append(str(bit))

    def startReceiver(self):
        t = threading.Thread(name='Receiver', target=self.receiveData)
        t.start()
        t.join()
                


    