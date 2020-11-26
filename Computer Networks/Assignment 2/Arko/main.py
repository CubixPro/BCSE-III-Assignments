import threading
import multiprocessing
import sender_StopNWait
import sender_GoBackN
import sender_Selective
from channel import *
from receiver import *
import const

def start():

    writeFromSenderToChannel = []
    readFromSenderToChannel = []

    writeFromChannelToSender = []
    readFromChannelToSender = []

    writeFromChannelToReceiver = []
    readFromChannelToReceiver = []

    writeFromReceiverToChannel = []
    readFromReceiverToChannel = []

    for i in range(const.totalSenderNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeFromSenderToChannel.append(writeHead) 
        readFromSenderToChannel.append(readHead) 

        readHead, writeHead = multiprocessing.Pipe()
        writeFromChannelToSender.append(writeHead)
        readFromChannelToSender.append(readHead)

    for i in range(const.totalReceiverNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeFromChannelToReceiver.append(writeHead) 
        readFromChannelToReceiver.append(readHead) 

        readHead, writeHead = multiprocessing.Pipe()
        writeFromReceiverToChannel.append(writeHead) 
        readFromReceiverToChannel.append(readHead) 

    senderList = []
    receiverList = []

    fileType = input("Choose the Data Link Layer Protocol---\n1. Stop and Wait\n2. Go Back N\n3. Selective Repeat\n Choose numbers --  ")

    if fileType == '1': 
        fileName = sender_StopNWait
        print("The chosen Protocol is Stop and Wait")
    elif fileType == '2': 
        fileName = sender_GoBackN
        print("The chosen Protocol is Go Back N")
    else: 
        fileName = sender_Selective
        print("The chosen Protocol is Selective Repeat")

    for i in range(const.totalSenderNumber):
        sender = fileName.Sender(
            i, 
            'input/input'+str(i)+'.txt', 
            writeFromSenderToChannel[i],
            readFromChannelToSender[i]
            )

        senderList.append(sender)

    for i in range(const.totalReceiverNumber):
        receiver = Receiver(
            i,
            writeFromReceiverToChannel[i],
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