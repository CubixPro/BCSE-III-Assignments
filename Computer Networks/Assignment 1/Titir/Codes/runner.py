from create_packet_all import *
from error_detection import *
from injecterror import *
#TODO MAKE NEW REPORT
#file_in = input("Enter file name: ")
file_in = "../Messages/message.txt"
file_out = "../Packets/packet.txt"
crc1 = "1100001100100110011111011"
file_rep = "report.txt"
crc2 = "10011"
countneither = 0
countall = 0
countv = 0
countl = 0
countcrc = 0
blocks = 4 
block_size = 8
choice = input("Do you want to input file name? (y/N)")
if choice == 'y':
    file_in = input("Enter file name: ")
choice = input("Do you want to input frame size and block size? (y/N)")
if choice == 'y':
    frame_size = int(input("Enter frame size : "))
    block_size = int(input("Enter block size : "))
    blocks = int(frame_size/block_size)

choice = input("Which CRC do you want to use? (4/24)")
if choice == 24:
    crc2 = crc1

rep = open(file_rep, "a")
for i in range(1):
    f = open(file_in, "w")
    for i in range(blocks * block_size):
        f.write(str(random.randrange(2)))
    f.close()
    convert_file(file_in, file_out, block_size, blocks, crc2)
    adderror(file_out)
    crc, cs, l, v = detect_error(file_out, crc2, block_size, blocks)
    #print(detect_error(file_out, crc2, block_size, blocks))
    if not crc and not cs and not l and not v:
        countall = countall + 1
    if crc and cs and l and v:
        countneither = countneither + 1
    if crc and not l:
        countl = countl + 1
        
    if crc and not v:
        countv = countv + 1
    if crc:
        countcrc = countcrc + 1
    
"""
print(countneither)
print(countall)
print(countv)
print(countl)
print(countcrc)
"""
"""
rep.write("Frame size : " + str(block_size*blocks) + "\n")
rep.write("CRC = " + crc2 + "\n")
rep.write(str(countneither) + " " + str(countall) + " " + str(countv) + " " + str(countcrc) + " " + str(countl))
rep.write("\n------------\n")
rep.close()
"""
if countv >= 1:
    print("CRC PASSED BUT VRC FAILED")
elif countl >= 1:
    print("CRC PASSED BUT LRC FAILED")
elif countneither >= 1:
    print("ALL ERROR DETECTION SCHEMES PASSED")
elif countall >= 1:
    print("ALL ERROR DETECTION SCHEMES FAILED")
