import threading
import random
import time
import sys
import os
from multiprocessing import Process, Pipe

# declared globally...can be declared inside monitor class also
maxBufferSize = 10
buffer = []


################################################################
################################################################
class Monitor:
    def __init__(self):
        self.condition  = threading.Condition()
        #self.busy       = false
    
    def getItem(self): # for consumers

        self.condition.acquire()
        while (len(buffer) <= 0):
            self.condition.wait() # put the process into a waiting queue

        # in this moment wait is over! Means item is available!
        # so get the item , release the lock and return the item to consumer
        item = buffer.pop(0)
        self.condition.release()
        return item 
    
    def makeItem(self, item):

        self.condition.acquire()
        while len(buffer) >= maxBufferSize:
            self.condition.wait()

        buffer.append(item)
        self.condition.notify()
        self.condition.release()


################################################################
################################################################

class Item:
    def __init__(self, _id, producer, payLoad):
        self.id         = _id
        self.producer   = producer
        self.payLoad    = payLoad
    
    def __str__(self):
        #string1 = "------------------------------------------\n"
        string2 = f"Item id: {self.id}\nItem Producer: {self.producer}\nItem Payload: {self.payLoad}\n"

        return string2

################################################################
################################################################

class Consumer:
    def __init__(self, _id, lock):
        self.id     = _id
        self.lock   = lock
    
    def consume(self, monitor): 
        string3 = "-"*40 + "\n"
        string2 = f"Consumer ID: {self.id}\n"
        string1 = f"---------------Consumer{self.id}---------------\n"

        while True:
            
            item = monitor.getItem() # monitor will take care of the synchronization
            print(string1 + str(item) + string3)
            time.sleep(random.random())
                
    def startConsuming(self, monitor):
        t = threading.Thread(name="Consumer"+str(self.id), target=self.consume, args=(monitor,))
        t.start()
        t.join()


################################################################
################################################################
class Producer:
    def __init__(self, _id, lock):
        self.id     = _id
        self.lock   = lock
        self.itemID = 1
        
    def produce(self, monitor):
        string1 = f"***************Producer{self.id}***************\n"
        string3 =  "*********************************************\n"

        while True:
            payload = random.randint(1000,9999)
            IDforItem = f"{self.itemID}/{self.id}"
            item = Item(IDforItem, self.id, payload)
            self.itemID += 1

            monitor.makeItem(item)# monitor will take care of the synchronization
            print(string1 +"Item Produced!!!\n"+ str(item) + string3)
            time.sleep(random.random())
    
    def startProducing(self, monitor):
        t = threading.Thread(name="Producer"+str(self.id), target=self.produce, args=(monitor,))
        t.start()
        t.join()


################################################################
################################################################

def start():

    producerNumber = int(input("Enter Number of producer: "))
    consumerNumber = int(input("Enter Number of consumer: "))
    maxBufferSize  = int(input("Enter max Buffer size: "))

    producerObjList = []
    consumerObjList = []

    lock = threading.Lock()

    for i in range(producerNumber):
        prod = Producer(i+1, lock)
        producerObjList.append(prod)

    for i in range(consumerNumber):
        cons = Consumer(i+1, lock)
        consumerObjList.append(cons)

    monitor = Monitor()

    pThreadList = []
    cThreadList = []
    count = 1
    for producer in producerObjList:
        t = threading.Thread(name="Producer"+str(count), target=producer.startProducing, args=(monitor,))
        pThreadList.append(t)
        count += 1

    count = 1
    for consumer in consumerObjList:
        t = threading.Thread(name="Consumer"+str(count), target=consumer.startConsuming, args=(monitor,))
        cThreadList.append(t)
        count += 1
    
    for thread in pThreadList:
        thread.start()
    for thread in cThreadList:
        thread.start()

    for thread in pThreadList:
        thread.join()
    for thread in pThreadList:
        thread.join()

if __name__ == "__main__":
    start()