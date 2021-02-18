import addErrorDetection, addError, packetCreator, errorDetection
import time
filenm = input("Enter the name of the file you want to send: ")
fileName = "../Messages/" + filenm
redundancyType = input("Which technique do you want?\n1. VRC\n2. LRC\n3. Checksum\n4. CRC\n5. All:::  ")

blockSize = 8
fileptr = open(fileName, "r")
temp_data = fileptr.read()
length = len(temp_data)

blocks = length/blockSize
blocks = int(blocks) 
fileptr.close()

crcCode = "10010"

outputFile = "../Messages/output.txt"

packetCreator.convert_message(fileName, outputFile, blockSize, blocks, crcCode)

consent = input("Do you want to inject errors?(y/n):  ")
if consent == "y":
    addError.inject_error(outputFile)

print("File is being sent..................")
time.sleep(1)
print("File sent !!!")

vrc, lrc, chksum, crc = errorDetection.detect_error(outputFile, crcCode, blockSize, blocks)

if redundancyType.lower() == 'vrc':
    if vrc:
        print("No error detected by the receiver!")
    else:
        print("The receiver received a corrupted packet.... Please retransmit!")

elif redundancyType.lower() == 'lrc':
    if lrc:
        print("No error detected by the receiver!")
    else:
        print("The receiver received a corrupted packet.... Please retransmit!")

elif redundancyType.lower() == 'checksum':
    if chksum:
        print("No error detected by the receiver!")
    else:
        print("The receiver received a corrupted packet.... Please retransmit!")

elif redundancyType.lower() == 'crc':
    if crc:
        print("No error detected by the receiver!")
    else:
        print("The receiver received a corrupted packet.... Please retransmit!")

elif redundancyType.lower() == 'all':
    print("Packet accepted by the VRC, LRC, CHECKSUM, CRC respectively:  ")
    print(vrc, lrc, chksum, crc)

print("**********************************************************************************************************")


