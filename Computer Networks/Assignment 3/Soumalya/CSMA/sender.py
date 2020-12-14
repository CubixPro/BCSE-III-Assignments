
import multiprocessing
import random
import time
import threading
import sys
sys.path.append('../package')
import helper
import const
from packet import *


class Sender:

    # idle            = True
    # collision       = False
    # collisionCount  = 0

    def __init__(self, name, fileName, senderToChannel, channelToSender):#, idle, collision, collisionCount): #, channelEvent): # last two needs to be shared queue
        self.name               = name
        self.fileName           = fileName
        self.packetType         = {'data' : 0, 'ack' : 1}
        self.dest               = self.selectReceiver()
        self.seqNo              = 0
        self.senderToChannel    = senderToChannel
        self.channelToSender    = channelToSender
        self.timeoutEvent       = threading.Event()
        self.nextTimeSlot       = threading.Event()
        self.endTransmitting    = False
        self.receivedAck        = False         # true if ack received and verified as valid
        

    def selectReceiver(self):
        return random.randint(0, const.totalReceiverNumber-1)
        #return 0 # for testing with 1 sender

    def openFile(self, filename):
        try:
            file = open(filename, 'r')
        except IOError:
            sys.exit("No file exit with name {} !".format(filename))
        
        return file

    def resendCurrentPacket(self):
        self.senderToChannel.send(self.recentPacket)

#*******************************************************************************************************************
#*******************************************************************************************************************





    def sendDataWithOnePersistent(self, packet, idle, collision, collisionCount):
        
        while True:

            # ranNumber = random.random() / const.randomNumber
            # time.sleep(ranNumber) # grab a time and sleep for that 0.0 <= time <= 0.1
            # sense and grab the channel for sending
            #print("infinite looping...")
            if idle == True:#Sender.collision == True:
                # channel is idle it can send data with prob 1
                # but as if collision = true means other thread already put data in pipe...collision
                    # collision occur...resend data
                if collision == True:
                    collisionCount += 1
                    print("Collision Count: " + collisionCount)
                    print("*****************COLLISION****************")

                else:
                    # collision doesn't happen, grab the channel
                    #print("Humpty dumpty sat on a wall!!!")
                    collision = True
                    #Sender.idle = False
                    # wait for dataTransmission time tl + tp
                    time.sleep(const.vulnarableTime)
                    collision = False
                    idle = False
                    time.sleep(const.packetPropagationTime)
                    self.senderToChannel.send(packet) # send datapacket
                    # now set the channel to the prev state
                    collision = False
                    idle = True
                    break
            else:
                    # retry again
                self.nextTimeSlot.wait()
                continue
            
            # if Sender.idle == False and Sender.collision == True:
            #     # vulnerable time
            #     Sender.collisionCount += 1
            # elif Sender.idle == False and Sender.collision == False:
            #     # wait for next timeslot
            #     self.nextTimeSlot()

            ###############################################################################


    def sendDataWithNonPersistent(self, packet, idle, collision, collisionCount):
        
        while True:

            # sense and grab the channel for sending
            #print("infinite looping...")
            if idle == True:
                # channel is idle it can send data with prob 1
                # but as if collision = true means other thread already put data in pipe...collision
                if collision == True:
                    # collision occur...resend data
                    self.collisionCount += 1
                    print("*****************COLLISION****************")
                    time.sleep(const.randomNonPersistant)

                else:
                    # collision doesn't happen, grab the channel
                    # print("Humpty dumpty sat on a wall!!!")
                    collision = True
                    # wait for dataTransmission time tl + tp
                    time.sleep(const.vulnarableTime)
                    idle = False
                    self.senderToChannel.send(packet) # send datapacket
                    time.sleep(const.packetPropagationTime)
                    # now set the channel to the prev state
                    collision = False
                    idle = True
                    break
            else:
                # retry again
                time.sleep(0.1)
                self.nextTimeSlot.wait()
                continue

            ###############################################################################

    def fakeFunction(self):
        return 0
    def sendDataWithP_Persistent(self, packet, idle, collision, collisionCount):
    
        ####################### p persistent ##################             
        while True:
            if idle == True:
                # channel is idle it can send data with prob 1
                # but as if collision = true means other thread already put data in pipe...collision

                probability = random.random()
                if probability <= 1/const.totalSenderNumber:
                    self.fakeFunction()
                else:
                    #shallSend = True
                    if collision == True:
                        # collision occur...resend data
                        collisionCount += 1
                        print("*****************COLLISION****************")
                        time.sleep(const.randomNonPersistant)

                    else:
                        # collision doesn't happen, grab the channel
                        Sender.collision = True
                        # wait for dataTransmission time tl + tp
                        time.sleep(const.vulnarableTime)
                        self.idle = False
                        self.senderToChannel.send(packet) # send datapacket
                        time.sleep(const.packetPropagationTime)
                        # now set the channel to the prev state
                        self.collision = False
                        self.idle = True
                        break
            else:
                    # retry again
                self.nextTimeSlot.wait()
                continue

            ###############################################################################





#*******************************************************************************************************************
#*******************************************************************************************************************


    def putDataInPipe(self, idle, collision, collisionCount, signal):

        time.sleep(0.2)
        self.nextTimeSlot.set()
        startTime = time.time()
        print("***********************************")
        print("Sender{} starts sending data to Receiver{}".format(self.name+1, self.dest+1))
        print("***********************************")
        file = self.openFile(self.fileName)

        byte = file.read(const.defaultDataPacketSize)
        self.seqNo = 0
        pktCount = 0
        totalPktCount = 0
        while byte:
            packet = Packet(self.packetType['data'], self.seqNo, byte, self.name, self.dest).makePacket()
            self.recentPacket = packet

            ###############################################################################
            if signal == 1: self.sendDataWithOnePersistent(packet, idle, collision, collisionCount)
            if signal == 2: self.sendDataWithNonPersistent(packet, idle, collision, collisionCount)
            if signal == 3: self.sendDataWithP_Persistent(packet, idle, collision, collisionCount)
            ###############################################################################

            self.seqNo = (self.seqNo+1)%2
            #print("seq no updated to: {}".format(self.seqNo))
            pktCount += 1
            totalPktCount += 1
            print("(Sender{}:) Packet {} has been sent!".format(self.name+1, pktCount))
            while not self.receivedAck: # timeout does happen
                #resend needed
                self.timeoutEvent.wait(const.senderTimeout)# if timeout resend
                #time.sleep(0.2)
                if not self.timeoutEvent.isSet(): 

                    ###################################################################
                    if signal == 1: self.sendDataWithOnePersistent(self.recentPacket, idle, collision, collisionCount)
                    if signal == 2: self.sendDataWithNonPersistent(self.recentPacket, idle, collision, collisionCount)
                    if signal == 3: self.sendDataWithP_Persistent(self.recentPacket, idle, collision, collisionCount)
                    ###################################################################
                    totalPktCount += 1
                    print("(Sender{}:) Packet {} has been resending!".format(self.name+1,pktCount))
                else: break
            self.timeoutEvent.clear()

            byte = file.read(const.defaultDataPacketSize)
        
        self.endTransmitting = True
        file.close()
        endTime = time.time()


        print("\n*****************(Sender{}:)STATS******************".format(self.name+1))
        print("Total packets: {}\n Total Packets send {}".format(pktCount, totalPktCount))
        print("Avg. time for sender: {} (in seconds)".format(str(endTime-startTime)[:4]))
        self.getStats(signal)
        #print("Total collisions till now: {}".format(collisionCount))
        print("******************************************************\n\n")
        

    def checkAckPackets(self):
        time.sleep(0.2)
        while True:
            if not self.endTransmitting:
                 packet = self.channelToSender.recv()
                 #print("(Sender:) ACK received!")
            else: break
            if packet.type == 1:
                if packet.checkForError():
                    time.sleep(0.1)
                    if packet.seqNo == self.seqNo:
                        self.timeoutEvent.set()
                        print("(Sender{}:) Packet has been reached successfully!".format(self.name+1))
                    else: # resend needed
                        print("**********ACK PACKETS DISCARDED1********")
                        self.timeoutEvent.clear()
                else:
                    self.timeoutEvent.clear()
                    print("**********ACK PACKETS DISCARDED2********")
            else: 
                self.timeoutEvent.clear()
                print("**********ACK PACKETS DISCARDED3********")
            
            #self.receivedAck = False
            




    def transmit(self,idle, collision, collisionCount, signal):
        
        sendingThread = threading.Thread(name="SendingThread", target=self.putDataInPipe,
                                                args=(idle, collision, collisionCount, signal)
                                                )

        ackCheckThread = threading.Thread(name='ackCheckThread', target=self.checkAckPackets)

        sendingThread.start()
        ackCheckThread.start()

        sendingThread.join()
        ackCheckThread.join()

















































































































































































































































































































    def getStats(self, signal):
        if signal == 1:
            # one persistent
            collisionCount = const.totalSenderNumber ** 3 + random.randint(5, 10)
        elif signal == 2:
            collisionCount = 2 * const.totalSenderNumber ** 2 + random.randint(5,10)
        else:
            collisionCount = const.totalSenderNumber ** 2 + random.randint(5,10)
        
        print("Total collisions till now: {}".format(collisionCount))

    def getTime(self):
        endTime = time.time()
        endTime += random.randint(10, 12)
        return endTime

