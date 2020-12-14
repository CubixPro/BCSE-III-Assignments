import random

totalSenderNumber       = 2
totalReceiverNumber     = 1
defaultDataPacketSize   = 36
senderTimeout           = 2

################### receiver consts
outFilePath             = "/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 3/1-persistant/output/"
################################################
# channel const
dropOutProb             = 0.1
injectErrorProb         = 0.3
delayProb               = 0.3
delay                   = 0.5 # in seconds
#########################################
# For GoBackNARQ

bitsForSeqNo            = 8
windowSize              = 5 # 2^8-1

####################################
# for CSMA

randomNumber            = 10
vulnarableTime          = 0.1 # data length / bandwidth
#propagationTime        = 0.1
packetPropagationTime   = 0.1 # channel remains busy this time


randomNonPersistant     = random.random()



