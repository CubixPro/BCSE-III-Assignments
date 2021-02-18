import threading
import multiprocessing
from sender import *
from channel import *
from receiver import *
import const

def start():

    #writeFromSenderToChannel = []
    #readFromSenderToChannel = []

    writeFromChannelToSender = []
    readFromChannelToSender = []

    writeFromChannelToReceiver = []
    readFromChannelToReceiver = []

    writeFromReceiverToChannel = []
    readFromReceiverToChannel = []

    for i in range(const.totalSenderNumber):

        readHead, writeHead = multiprocessing.Pipe()
        writeFromChannelToSender.append(writeHead)
        readFromChannelToSender.append(readHead)

    for i in range(const.totalReceiverNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeFromChannelToReceiver.append(writeHead) 
        readFromChannelToReceiver.append(readHead) 

    readFromSenderToChannel, writeFromSenderToChannel = multiprocessing.Pipe()

    senderList = []
    receiverList = []

    technique = int(input("The CSMA technique you want to use\n1. One Persistent Method\n2. Non Persistent Method\n3. P-Persistent Method\nChoose one of the following - "))

    for i in range(const.totalSenderNumber):
        sender = Sender( i, 
            'input/input'+str(i)+'.txt', 
            writeFromSenderToChannel,
            readFromChannelToSender[i],
            technique
            )

        senderList.append(sender)

    for i in range(const.totalReceiverNumber):
        receiver = Receiver(
            i,
            readFromChannelToReceiver[i],
        )

        receiverList.append(receiver)

    channel = Channel(
        readFromSenderToChannel,
        writeFromChannelToSender,
        readFromReceiverToChannel,
        writeFromChannelToReceiver
    )

    senderThreads = []
    receiverThreads = []

    for i in range(len(senderList)):
        p = threading.Thread(target=senderList[i].transmit)
        senderThreads.append(p)
    
    for i in range(len(receiverList)):
        p = threading.Thread(target=receiverList[i].startReceiving)
        receiverThreads.append(p)
    
    channelThread = threading.Thread(target= channel.startChannel)

    channelThread.start()

    for thread in receiverThreads:
        thread.start()
        
    for thread in senderThreads:
        thread.start()

    for thread in senderThreads:
        thread.join()
    
    channelThread.join()

    for thread in receiverThreads:
        thread.join()
    
if __name__ == "__main__": 
    start()