import multiprocessing
import random
import time
import threading
import sys
#sys.path.append('../package')
import const

# thread.Lock
# release and acquire

class Sender:
    def __init__(self, name, fileName, walshCode, senderToChannel, nextTimeSlot, lock):
        self.name               = name
        self.fileName           = fileName
        self.senderToChannel    = senderToChannel # a pipe
        self.walshCode          = walshCode # tuple containg walshCode
        self.nextTimeSlot       = nextTimeSlot # threading object
        self.lock               = lock

    
    def openFile(self, fileName):
        try:
            file = open("./input/"+fileName, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(fileName))

        return file
    
    def sendData(self):
        startTime = time.time()
        file = self.openFile(self.fileName)

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
                self.lock.acquire()
                self.senderToChannel.send(dataToSend)
                self.lock.release()
                ##############################################
                self.nextTimeSlot.wait()

            byte = file.read(const.defaultDataPacketSize)
            
        
        

        while(True):
            silent = 0
            self.senderToChannel.send(silent)
            self.nextTimeSlot.wait()
            #time.sleep(0.05)
    

    def startSender(self):
        senderThread = threading.Thread(name="sender"+str(self.name+1),
                                        target=self.sendData)
        
        senderThread.start()
        senderThread.join()
        
        


            



