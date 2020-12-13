import multiprocessing
from sender import *
from ackDispatcher import *
from pktDispatcher import *
from channel import *
from receiver import *
import sys
sys.path.append('../package')
import const


##################################################
# need to change the interface
##################################################

def start():

    # pipe 1st obj can write....2nd obj can read
    # writeHeadOfSenderToChannelPipe = []
    # readHeadOfSenderToChannelPipe = []

    writeHeadOfACKDispatcherToSenderPipe = []
    readHeadOfACKDispatcherToSenderPipe = []


    writeHeadOfPktDispatcherToReceiverPipe = []
    readHeadOfPktDispatcherToReceiverPipe = []

    writeHeadOfReceiverToPktDispatcherPipe = []
    readHeadOfReceiverToPktDispatcherPipe = []

    for i in range(const.totalSenderNumber):
        # readHead, writeHead = multiprocessing.Pipe()
        # writeHeadOfSenderToChannelPipe.append(writeHead) # goes to sender
        # readHeadOfSenderToChannelPipe.append(readHead) # goes to channel

        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfACKDispatcherToSenderPipe.append(writeHead)# goes to channel
        readHeadOfACKDispatcherToSenderPipe.append(readHead) #goes to sender

    for i in range(const.totalReceiverNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfPktDispatcherToReceiverPipe.append(writeHead) # to channel
        readHeadOfPktDispatcherToReceiverPipe.append(readHead) # to receiver

        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfReceiverToPktDispatcherPipe.append(writeHead) #goes to receiver
        readHeadOfReceiverToPktDispatcherPipe.append(readHead) # goes to channel


    readHeadOfSenderToChannelPipe, writeHeadOfSenderToChannelPipe       = multiprocessing.Pipe()
    readHeadOfchannelToPktDispatcher, writeHeadOfchannelToPktDispatcher = multiprocessing.Pipe()
    readHeadOfPktDispatcherToChannel, writeHeadOfPktDispatcherToChannel = multiprocessing.Pipe()
    readHeadOfChannelToACKDispatcher, writeHeadOfChannelToACKDispatcher = multiprocessing.Pipe()
    ######################################
    # make the sender list receiver list and channel object
    #######################################

    senderList = []
    receiverList = []

    idle = True
    collision = False
    collisionCount = 0

    for i in range(const.totalSenderNumber):
        sender = Sender(
            i, 
            'input'+str(i)+'.txt', 
            writeHeadOfSenderToChannelPipe,# needs to be changed with a queue
            readHeadOfACKDispatcherToSenderPipe[i],
            idle,
            collision,
            collisionCount
            )

        senderList.append(sender)

    for i in range(const.totalReceiverNumber):
        receiver = Receiver(
            i,
            writeHeadOfReceiverToPktDispatcherPipe[i],
            readHeadOfPktDispatcherToReceiverPipe[i],
            False
        )

        receiverList.append(receiver)
    
    ############################
    # creating channel object
    ############################

    # print("Length of readHeadOfSenderToChannelPipe: ", len(readHeadOfSenderToChannelPipe))
    # print("Length of writeHeadOfChannelToSenderPipe: ", len(writeHeadOfChannelToSenderPipe))
    # print("Length of readHeadOfReceiverToChannelPipe: ", len(readHeadOfReceiverToChannelPipe))
    # print("Length of writeHeadOfChannelToReceiverPipe: ", len(writeHeadOfChannelToReceiverPipe))

    channel = Channel(
        0,
        readHeadOfSenderToChannelPipe, # just one pipe
        writeHeadOfchannelToPktDispatcher,
        readHeadOfPktDispatcherToChannel,
        writeHeadOfChannelToACKDispatcher
    )

    pktDispatcher = PktDispatcher(
        0,
        readHeadOfchannelToPktDispatcher,
        writeHeadOfPktDispatcherToChannel,
        writeHeadOfPktDispatcherToReceiverPipe,
        readHeadOfReceiverToPktDispatcherPipe
    ) 

    ackDispatcher = ACKDispatcher(
        0,
        readHeadOfChannelToACKDispatcher,
        writeHeadOfACKDispatcherToSenderPipe
    )

    #####################################################
    # multiprocessing starts
    #####################################################
    senderProcess = []
    receiverProcess = []

    for i in range(len(senderList)):
        p = multiprocessing.Process(target=senderList[i].transmit)
        senderProcess.append(p)
    
    for i in range(len(receiverList)):
        p = multiprocessing.Process(target=receiverList[i].startReceiving)
        receiverProcess.append(p)
    
    channelProcess = multiprocessing.Process(target= channel.startChannel)
    pktDispatcherProcess = multiprocessing.Process(target=pktDispatcher.startDispatcher)
    ackDispatcherProcess = multiprocessing.Process(target=ackDispatcher.startACKDispatcher)

    for process in senderProcess:
        process.start()
    
    channelProcess.start()
    pktDispatcherProcess.start()
    ackDispatcherProcess.start()

    for process in receiverProcess:
        process.start()

    for process in senderProcess:
        process.join()
    
    channelProcess.join()
    pktDispatcherProcess.join()
    ackDispatcherProcess.join()

    for process in receiverProcess:
        process.join()


    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("********************END***************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    print("**************************************************")
    
    


if __name__ == "__main__":
    start()