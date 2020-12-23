import multiprocessing
import random
import time
import threading
import sys
sys.path.append('../Assignment 4')
import const


class Sender:
    def __init__(self, name, walshCode, senderToChannel):
        self.name                   = name
        self.senderToChannel        = senderToChannel # a pipe
        self.walshCode              = walshCode # need the matrix
        self.data                   = dict()
               

    
    def openFile(self, fileName):
        try:
            file = open("./input/"+fileName, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(fileName))

        return file
    
    def sendData(self):
        self.preProcessing()
        print("(Sender:)Preprocessing done!!!")
        length = len(self.data[1])


        for i in range(length):
            dataToSend = [0 for k in range(len(self.walshCode[0]))]
            for j in range(1,const.totalSenderNumber+1):
                tempData = self.data[j][i] #list
                for k in range(len(self.walshCode[0])):
                    dataToSend[k] += tempData[k]
            
            self.senderToChannel.send(dataToSend)



    def preProcessing(self):
        for i in range(1,const.totalSenderNumber+1):
            fileName = "input"+str(i)+".txt"
            self.data[i] = []
            file = self.openFile(fileName)
            byte = file.read(const.defaultDataPacketSize)
            while byte:
                data1 = '{0:08b}'.format(ord(byte))

                for j in range(len(data1)):
                    dataToAppend = [] 
                    dataBit = int(data1[j])
                    if dataBit == 0: dataBit = -1

                    for k in self.walshCode[i-1]:
                        dataToAppend.append(k * dataBit)
                    
                    self.data[i].append(dataToAppend)
                byte = file.read(const.defaultDataPacketSize)

        #print(self.data)

                



    def startSender(self):
        senderThread = threading.Thread(name="sender"+str(self.name+1),
                                        target=self.sendData)
        
        senderThread.start()
        senderThread.join()
        
        


            



