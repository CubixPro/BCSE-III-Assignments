import threading
import random
import time
import sys
import os
import multiprocessing

dataBase = [0 for i in range(10)] # treating an array of integer as db


################################################################
################################################################

# class Request:

#     def __init__(self, _type):
#         self.type = _type
#         # type = 0 -> reader
#         # type = 1 -> writer


################################################################
################################################################

class Writer:
    def __init__(self, name):
        self.name = name
    
    def updateDB(self, monitor):
        string1 = f"***************Producer{self.name}***************\n"
        string3 =  "*********************************************\n"
        while True:
            pos = random.randint(0,9)
            value = random.randint(-10, 20)

            monitor.requestForUpdate(pos, value)
            print(string1 +"Updated Successfully!!!\n"+ string3)
            time.sleep(random.random())

    def start(self, monitor):
        t = threading.Thread(name="Writer"+str(self.name), target=self.updateDB, args=(monitor,))
        t.start()
        t.join()

################################################################
################################################################

class Reader:

    def __init__(self, name):
        self.name = name
    
    def read(self, monitor):
        string3 = "-"*40 + "\n"
        string2 = f"Reader ID: {self.name}\n"
        string1 = f"---------------Reader{self.name}---------------\n"

        while True:
            db = monitor.requestForRead()
            print(string1 + "Current DB is: " + str(db)+ "\n" + string3)
            time.sleep(random.random())

    def start(self, monitor):
        t = threading.Thread(name="Reader"+str(self.name), target=self.read, args=(monitor,))
        t.start()
        t.join()

################################################################
################################################################


class Monitor:
    def __init__(self):
        self.condition = threading.Condition()
        self.busy = False

    def requestForRead(self):

        while self.busy:
            time.sleep(0.2) # giving more timeout than writer, gives less priority to reader
        
        db = dataBase
        return db

    def requestForUpdate(self, pos, value):
        self.condition.acquire()
        while self.busy:
            self.condition.wait(0.1) # less timeout than reader hence more priority
        
        self.busy = True
        # now update dataBase
        dataBase[pos] = value
        self.busy = False
        self.condition.notify()
        self.condition.release()

################################################################
################################################################

def start():

    writerNumber = int(input("Enter Number of writers: "))
    readerNumber = int(input("Enter Number of readers: "))

    writerObjList = []
    readerObjList = []


    for i in range(writerNumber):
        writer = Writer(i+1)
        writerObjList.append(writer)

    for i in range(readerNumber):
        reader = Reader(i+1)
        readerObjList.append(reader)

    monitor = Monitor()

    wThreadList = []
    rThreadList = []
    count = 1
    for writer in writerObjList:
        t = threading.Thread(name="Writer"+str(count), target=writer.start, args=(monitor,))
        wThreadList.append(t)
        count += 1

    count = 1
    for consumer in readerObjList:
        t = threading.Thread(name="Reader"+str(count), target=reader.start, args=(monitor,))
        rThreadList.append(t)
        count += 1
    
    for thread in wThreadList:
        thread.start()
    for thread in rThreadList:
        thread.start()

    for thread in wThreadList:
        thread.join()
    for thread in rThreadList:
        thread.join()

if __name__ == "__main__":
    start()