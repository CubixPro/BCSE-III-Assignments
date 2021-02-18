
import os 
import random
def eject_error(filename):
    consent = input("Do you want to eject error?(y/n)")
    if consent == 'y':
        file = open("/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/" + filename, "wb+")
        filename = "/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/" + filename
        bits = int(input("Enter no of errors you want to introduce: "))
        no_of_bytes = nr_of_bytes = os.path.getsize(filename)
        for _ in range(bits):
            byteNo = random.randint(0,no_of_bytes)
            file.seek(byteNo,0)
            byte = file.read(1)
            #file.seek(-1,1) # writing position
            val = int.from_bytes(byte, byteorder='big')
            randVal = random.randint(1,7)
            #mask = 1 << randVal
            val = val ^ (1<<(randVal-1))
            file.write(val.to_bytes(1,byteorder='big'))
        print("Error Introduced!")
        file.close()
    
    else:
        print("No error introduced!")


