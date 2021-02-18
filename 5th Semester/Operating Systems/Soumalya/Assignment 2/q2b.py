import threading
import time
import sys
import os
from multiprocessing import Process, Pipe

listeners = 5

#########################################################
#########################################################

class BroadCaster:
    def __init__(self, name, broadCasterToListeners):
        self.name                   = name
        self.broadCasterToListeners = broadCasterToListeners

    def sendData(self):
        while True:
            print("-----------------------------------------------")
            # God knows why I am getting a error in this input statement
            msg = input("Enter your String: ")
            #msg = "Hola I am Broadcaster!"
            print("-----------------------------------------------")
            for i in range(listeners):
                self.broadCasterToListeners[i].send(msg)
            time.sleep(1)
            
    def start(self):
        t = threading.Thread(name="BroadcastThread", target=self.sendData)
        t.start()
        t.join()    

#########################################################
#########################################################


class Listener:
    def __init__(self, name, broadCasterToListeners):
        self.name                   = name
        self.broadCasterToListeners = broadCasterToListeners
    
    def receiveData(self):
        while True:
            data = self.broadCasterToListeners.recv()
            print("({}:) Gets msg from Broadcaster: {} Pid = {}".format(self.name, data, os.getpid()))
    
    def start(self):
        t = threading.Thread(name="ListenerThread", target=self.receiveData)
        t.start()
        t.join() 

#########################################################
#########################################################

def start():
    
    readHeadList = []
    writeHeadList = []

    for i in range(listeners):
        readHead, writeHead = Pipe()
        readHeadList.append(readHead)
        writeHeadList.append(writeHead)
    
    broadCast = BroadCaster("BroadCaster", writeHeadList)
    listenerList = []

    for i in range(listeners):
        listener = Listener("Listener"+str(i+1), readHeadList[i])
        listenerList.append(listener)
    
    # create process
    broadCastProcess = Process(name="BroadCaster", target=broadCast.start)

    processList = []
    for i in range(listeners):
        p = Process(name="Listener"+str(i+1), target=listenerList[i].start)
        processList.append(p)
    

    broadCastProcess.start()
    for process in processList:
        process.start()

    for process in processList:
        process.join()

    broadCastProcess.join()

if __name__ == "__main__":
    start()

