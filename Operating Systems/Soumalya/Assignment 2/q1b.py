import random
import os
import time
import threading
from multiprocessing import Process, Lock, Event

iteration = 10
semaphore1 = Event(
semaphore2 = Event()
lock = Lock()


def execute1(name, semaphore1, semaphore2):
    for i in range(iteration):
        print("({}:) Process ID: {}\n iteration: {}".format(name,os.getpid(), i+1))
        semaphore1.set()
        time.sleep(0.05)
        semaphore2.wait()
        semaphore1.clear()
        if(i == iteration-1): semaphore1.set()

def execute2(name, semaphore1,semaphore2):
    for i in range(iteration):
        print("({}:) Process ID: {}\niteration: {}".format(name,os.getpid(), i+1))
        semaphore2.set()
        time.sleep(0.05)
        semaphore1.wait()
        semaphore2.clear()
        if(i == iteration-1): semaphore2.set()


def start():
    process1 = Process(name="Process1", target=execute1, args=("Process1", semaphore1, semaphore2))
    process2 = Process(name="Process2", target=execute2, args=("Process2", semaphore1, semaphore2))

    process1.start()
    process2.start()

    process1.join()
    process2.join()

if __name__ == "__main__":
    start()