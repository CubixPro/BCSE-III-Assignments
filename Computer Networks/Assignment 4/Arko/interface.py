import multiprocessing
import random
import time
import threading
import sys
from sender import *
from receiver import *
from channelFile import *
#sys.path.append('../package')
import const


def getNextPowerof2(num):
    power = 1
    while(power < num):
        power *= 2
    return power


def buildWalshTable(length, i1,i2, j1,j2, isComplement):
    if length == 2:
        if not isComplement:
            wTable[i1][j1] = 1
            wTable[i1][j2] = 1
            wTable[i2][j1] = 1
            wTable[i2][j2] = -1
        else:
            wTable[i1][j1] = -1
            wTable[i1][j2] = -1
            wTable[i2][j1] = -1
            wTable[i2][j2] = 1
        
        return
    
    midi = (i1+i2)//2
    midj = (j1+j2)//2

    buildWalshTable(length/2, i1, midi, j1, midj, isComplement)
    buildWalshTable(length/2, i1, midi, midj+1, j2, isComplement)
    buildWalshTable(length/2, midi+1, i2, j1, midj, isComplement)
    buildWalshTable(length/2, midi+1, i2, midj+1, j2, not isComplement)

    return

def start(wTable):

    writeHeadOfChannelToReceiverPipeList = []
    readHeadOfChannelToReceiverPipeList = []

    readHeadOfSenderToChannelPipe, writeHeadOfSenderToChannelPipe = multiprocessing.Pipe()

    for i in range(const.totalReceiverNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfChannelToReceiverPipeList.append(writeHead)
        readHeadOfChannelToReceiverPipeList.append(readHead)

    # initialize the tables and objects

    senderList = []
    receiverList = []

    for i in range(const.totalSenderNumber):
        sender = Sender(
            i, 
            wTable[i], 
            writeHeadOfSenderToChannelPipe,
        )
        senderList.append(sender)
    
    for i in range(const.totalReceiverNumber):
        receiver = Receiver(
            i,
            wTable,
            readHeadOfChannelToReceiverPipeList[i],
        )
        receiverList.append(receiver)
    
    channelObj = Channel(
        0, 
        readHeadOfSenderToChannelPipe, # single pipe 
        writeHeadOfChannelToReceiverPipeList,
    )

    
    # initializing the processes
    senderProcess = []
    receiverProcess = []

    for i in range(len(senderList)):
        p = threading.Thread(name="Sender" + str(i+1),target=senderList[i].startSender)
        senderProcess.append(p)
    
    for i in range(len(receiverList)):
        p = threading.Thread(name="Receiver"+str(i+1), target=receiverList[i].startReceiver)
        receiverProcess.append(p)
    
    channelProcess = threading.Thread(name="ChannelP", target=channelObj.startChannel)

    # initialize the product
    channelProcess.start()
    for process in receiverProcess:
        process.start()

    for process in senderProcess:
        process.start()

    for process in senderProcess:
        process.join()

    for process in receiverProcess:
        process.join()
    channelProcess.join()
    

if __name__ == "__main__":
    num = getNextPowerof2(const.totalSenderNumber)
    wTable = [[0 for i in range(num)] for j in range(num)]

    if const.totalSenderNumber >1: buildWalshTable(num, 0, num - 1, 0, num - 1, False)
    else: wTable = [1]
    print(wTable)
    
    start(wTable)
