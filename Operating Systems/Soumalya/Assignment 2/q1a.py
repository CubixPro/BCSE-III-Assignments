import random
import os
import time
from multiprocessing import Process, current_process 

iteration = 10
def execute(name):
    for i in range(iteration):
        print("({}:) Process ID: {}\n iteration: {}".format(name,os.getpid(), i+1))
        time.sleep(random.random())

def start():
    process1 = Process(name="Process1", target=execute, args=("Process1",))
    process2 = Process(name="Process2", target=execute, args=("Process2",))

    process1.start()
    process2.start()

    process1.join()
    process2.join()

if __name__ == "__main__":
    start()