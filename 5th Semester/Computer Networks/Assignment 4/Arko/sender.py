import multiprocessing
import random
import time
import threading
import sys
import const

class Sender:
    def __init__(self, name, walshCode, senderToChannel):
        self.name               = name
        self.senderToChannel    = senderToChannel # a pipe
        self.walshCode          = walshCode # tuple containg walshCode
   
    def openFile(self, sender):
        try:
            file = open(const.inputFilePath+'input'+str(sender+1)+'.txt', 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(fileName))

        return file
    
    def sendData(self):
        startTime = time.time()
        file = self.openFile(self.name)

        totalBitSent = 0
        byte = file.read(const.defaultDataPacketSize)
        while byte:

            # send the data bits of byte
            data = '{0:08b}'.format(ord(byte))
            for i in range(len(data)):
                dataToSend = []
                dataBit = int(data[i])
                if dataBit == 0: dataBit = -1
               

                for j in self.walshCode:
                    dataToSend.append(j * dataBit)
                ##############################################
                self.senderToChannel.send(dataToSend)
                ##############################################
                print("(Sender{}:) data bit send {}".format(self.name+1, dataBit))
                time.sleep(1)

            byte = file.read(const.defaultDataPacketSize)
        
        print("(Sender{}:) DONE SENDING...".format(self.name + 1))
    

    def startSender(self):
        senderThread = threading.Thread(name="sender"+str(self.name+1),
                                        target=self.sendData)
        
        senderThread.start()
        senderThread.join()
