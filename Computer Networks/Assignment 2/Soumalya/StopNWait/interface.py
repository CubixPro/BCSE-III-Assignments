
import multiprocessing
from sender import *
from channel import *
from receiver import *
sys.path.append('../package')
import const


def start():

    # pipe 1st obj can write....2nd obj can read
    writeHeadOfSenderToChannelPipe = []
    readHeadOfSenderToChannelPipe = []

    writeHeadOfChannelToSenderPipe = []
    readHeadOfChannelToSenderPipe = []


    writeHeadOfChannelToReceiverPipe = []
    readHeadOfChannelToReceiverPipe = []

    writeHeadOfReceiverToChannelPipe = []
    readHeadOfReceiverToChannelPipe = []

    for i in range(const.totalSenderNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfSenderToChannelPipe.append(writeHead) # goes to sender
        readHeadOfSenderToChannelPipe.append(readHead) # goes to channel

        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfChannelToSenderPipe.append(writeHead)# goes to channel
        readHeadOfChannelToSenderPipe.append(readHead) #goes to sender

    for i in range(const.totalReceiverNumber):
        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfChannelToReceiverPipe.append(writeHead) # to channel
        readHeadOfChannelToReceiverPipe.append(readHead) # to receiver

        readHead, writeHead = multiprocessing.Pipe()
        writeHeadOfReceiverToChannelPipe.append(writeHead) #goes to receiver
        readHeadOfReceiverToChannelPipe.append(readHead) # goes to channel


    ######################################
    # make the sender list receiver list and channel object
    #######################################

    senderList = []
    receiverList = []

    for i in range(const.totalSenderNumber):
        sender = Sender(
            i, 
            'input'+str(i)+'.txt', 
            writeHeadOfSenderToChannelPipe[i],
            readHeadOfChannelToSenderPipe[i]
            )

        senderList.append(sender)

    for i in range(const.totalReceiverNumber):
        receiver = Receiver(
            i,
            writeHeadOfReceiverToChannelPipe[i],
            readHeadOfChannelToReceiverPipe[i],
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
        readHeadOfSenderToChannelPipe,
        writeHeadOfChannelToSenderPipe,
        readHeadOfReceiverToChannelPipe,
        writeHeadOfChannelToReceiverPipe
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


    for process in senderProcess:
        process.start()
    
    channelProcess.start()

    for process in receiverProcess:
        process.start()

    for process in senderProcess:
        process.join()
    
    channelProcess.join()

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