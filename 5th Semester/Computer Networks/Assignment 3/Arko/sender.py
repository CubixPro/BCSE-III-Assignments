import multiprocessing
import random
import time
import threading
import helper
import const
from createPacket import *


class Sender:
    def __init__(self, name, fileName, senderToChannel, channelToSender, collisionTechnique): 
        self.name               = name
        self.fileName           = fileName
        self.packetType         = {'data' : 0, 'ack' : 1}
        self.dest               = self.selectReceiver()
        self.senderToChannel    = senderToChannel
        self.channelToSender    = channelToSender
        self.timeoutEvent       = threading.Event()
        self.endTransmitting    = False
        self.start              = 0
        self.seqNo              = 0
        self.pktCount           = 0
        self.collisionTechnique = collisionTechnique
        self.busy               = 0
        self.collisionCount     = 0

    def selectReceiver(self):
        return self.name

    def openFile(self, filename):
        try:
            file = open(filename, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(filename))
        
        return file

    def sendDataWithOnePersistent(self, packet):

        while True:

            if self.busy == 0:

                file = self.openFile("collision.txt")
                collision = file.read()
                file.close()

                if collision == '1':
                    self.collisionCount += 1
                    print("SENDER{} -->> COLLISION".format(self.name+1))
                    time.sleep(const.CollisionWaitTime)

                else:
                    print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, self.pktCount+1))

                    file = open('collision.txt',"w")
                    file.write(str(1))
                    file.close()
                    
                    time.sleep(const.vulnerableTime)

                    file = open('collision.txt',"w")
                    file.write(str(0))
                    file.close()

                    self.senderToChannel.send(packet) 
                    time.sleep(const.propagationTime)
                    break

            else:
                print("SENDER{} -->> FOUND CHANNEL BUSY".format(self.name+1))
                time.sleep(0.5)
                continue

    def sendDataWithNonPersistent(self, packet):

       while True:

            if self.busy == 0:

                file = self.openFile("collision.txt")
                collision = file.read()
                file.close()

                if collision == '1':
                    self.collisionCount += 1
                    print("SENDER{} -->> COLLISION".format(self.name+1))
                    time.sleep(const.collisionWaitTime)

                else:
                    print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, self.pktCount+1))

                    file = open('collision.txt',"w")
                    file.write(str(1))
                    file.close()
                     
                    time.sleep(const.vulnerableTime)

                    file = open('collision.txt',"w")
                    file.write(str(0))
                    file.close()

                    self.senderToChannel.send(packet)
                    time.sleep(const.propagationTime)
                    break

            else:
                print("SENDER{} -->> FOUND CHANNEL BUSY".format(self.name+1))
                time.sleep(const.nonPersistantWaitingTime)
                continue

    def sendDataWithP_Persistent(self, packet):

        while True:

            if self.busy == 0:
                prob = random.random()

                if(prob <= 0.5):
                    file = self.openFile("collision.txt")
                    collision = file.read()
                    file.close()

                    if collision == '1':
                        self.collisionCount += 1
                        print("SENDER{} -->> COLLISION OCCURED".format(self.name+1))
                        time.sleep(const.CollisionWaitTime)

                    else:
                        print("SENDER{} -->> PACKET {} SENT TO CHANNEL".format(self.name+1, self.pktCount+1))

                        file = open('collision.txt',"w")
                        file.write(str(1))
                        file.close()
                         
                        time.sleep(const.vulnerableTime)

                        file = open('collision.txt',"w")
                        file.write(str(0))
                        file.close()

                        self.senderToChannel.send(packet) 
                        time.sleep(const.propagationTime)
                        break

                else:
                    print("SENDER{} -->> WAITING".format(self.name+1))
                    time.sleep(const.timeSlot)

            else:
                print("SENDER{} -->> FOUND CHANNEL BUSY".format(self.name+1))
                time.sleep(0.5)
                continue

    def dataIntoFrames(self):

        print("SENDER{} starts sending data to RECEIVER{}".format(self.name+1, self.dest+1))
        self.start = time.time()

        file = self.openFile(self.fileName)
        byte = file.read(const.defaultDataPacketSize)
        self.seqNo = 0
        while byte:
            packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
            self.recentPacket = packet
            if(self.collisionTechnique == 1): self.sendDataWithOnePersistent(packet)
            elif(self.collisionTechnique == 2): self.sendDataWithNonPersistent(packet)
            else: self.sendDataWithP_Persistent(packet)
            self.pktCount += 1

            byte = file.read(const.defaultDataPacketSize)
            if len(byte) == 0: break
            elif len(byte) < const.defaultDataPacketSize: 
                tempLength = len(byte)
                for char in range(const.defaultDataPacketSize - tempLength):
                    byte += '\0'
        
        self.endTransmitting = True
        file.close()

        print("\n*****************SENDER{} -->> STATS******************".format(self.name+1))
        print("Total packets: {}".format(self.pktCount))
        print("Total Delay:", round(time.time() - self.start, 2), "secs")
        print("Total collisions: {}".format(self.collisionCount))
        print("Throughput: {}\n".format(round(self.pktCount/(self.pktCount + self.collisionCount), 3)))

    def senseSignal(self):

        while True:
            if(self.channelToSender.recv() == '1'):
                self.busy = 1
            else:
                self.busy = 0

    def transmit(self):

        sendingThread = threading.Thread(name="sendingThread", target=self.dataIntoFrames)
        receivingSignalThread = threading.Thread(name="receivingSingalThread", target=self.senseSignal)

        sendingThread.start()
        receivingSignalThread.start()

        sendingThread.join()
        receivingSignalThread.join()