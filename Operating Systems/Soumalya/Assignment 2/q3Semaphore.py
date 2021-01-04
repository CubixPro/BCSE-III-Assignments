import threading
import random
import time
import sys
import os
from multiprocessing import Process, Pipe

lock = threading.Lock()
maxBufferSize = 10
buffer = []

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
    
    def consume(self): 
        string3 = "-"*40 + "\n"
        string2 = f"Consumer ID: {self.id}\n"
        string1 = f"---------------Consumer{self.id}---------------\n"

        while True:
            self.lock.acquire()
            if len(buffer) > 0:
                item = buffer.pop(0)
                print(string1 + str(item) + string3)
            else:
                print(string1 + "Buffer is empty!!!\n" + string3)

            self.lock.release()
            time.sleep(random.random())
                
    def startConsuming(self):
        t = threading.Thread(name="Consumer"+str(self.id), target=self.consume)
        t.start()
        t.join()


################################################################
################################################################
class Producer:
    def __init__(self, _id, lock):
        self.id     = _id
        self.lock   = lock
        self.itemID = 1
        
    def produce(self):
        string1 = f"***************Producer{self.id}***************\n"
        string3 =  "*********************************************\n"

        while True:
            payload = random.randint(1000,9999)
            IDforItem = f"{self.itemID}/{self.id}"
            item = Item(IDforItem, self.id, payload)
            self.itemID += 1
            self.lock.acquire()
            if len(buffer) < maxBufferSize:
                buffer.append(item)
                print(string1 +"Item Produced!!!\n"+ str(item) + string3)
            else:
                print(string1 + "Buffer is full!!!\n" + string1)

            self.lock.release()
            time.sleep(random.random())
    
    def startProducing(self):
        t = threading.Thread(name="Producer"+str(self.id), target=self.produce)
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

    pThreadList = []
    cThreadList = []
    count = 1
    for producer in producerObjList:
        t = threading.Thread(name="Producer"+str(count), target=producer.startProducing)
        pThreadList.append(t)
        count += 1
    count = 1
    for consumer in consumerObjList:
        t = threading.Thread(name="Consumer"+str(count), target=consumer.startConsuming)
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