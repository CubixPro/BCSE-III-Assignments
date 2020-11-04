from encryption import *
from decryption import *
from adderror import *
import random

crc_poly = "10011"
file_in = input("Enter file name : ")
file_out = 'out.txt'
frame_size = int(input("Enter frame size : "))
block_size = int(input("Enter block size : "))
blocks = int(frame_size/block_size)

f = open(file_in, "r")
text = f.readline()
f.close()
#print(text)
f = open(file_in, "w")
for i in range( min(len(text), blocks * block_size)):
    f.write(text[i])
for i in range( len(text), blocks * block_size):
    f.write(str(random.randrange(2)))
f.close()

change_crc = input("Do you want to change the default crc polynomial(default: 10011)? (y/n) ")
if(change_crc == 'y'):
    crc_poly = input("Enter the new crc polynomial(consists of only 0/1): ")

convert_file(file_in, file_out, block_size, blocks, crc_poly)
error_count = int(input("Enter the number of errors you want to inject : "))
adderror(file_out, error_count, frame_size)

f = open(file_out, "r")
text = f.readline()
f.close()
#print(text)
method = input("Enter the method by which you want to decrypt!\n1. VRC\n2. LRC\n3. CRC\n4. Checksum\nEnter the name: ") 

if(method.lower() == 'vrc'):
    res = vrc_check(text, frame_size, block_size)
elif(method.lower() == 'lrc'):
    res = lrc_check(text, frame_size, block_size)
elif(method.lower() == 'crc'):
    res = crc_check(text, frame_size, block_size, crc_poly)
else:
    res = checksum_check(text, frame_size, block_size)

if(res):
    print("No error detected by", method.lower(), "File received successfully!")
else:
    print("Corrupted File detected by", method.lower(), "Request for retransmission!")