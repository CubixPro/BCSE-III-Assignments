
import sys
sys.path.append('../package')
import const, helper

###################################################################################
# VRC method
##################################################################################
def VRC(filename):

    print("Generating redundancy using VRC technique")
    try:
        inFile = open(filename, 'r')
    except IOError:
        sys.exit("No such file exists!")

    outFile = open("/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/VRCOutput.dat","wb")
    print("Output file \"VRCOutput.dat\" created!")
    byte = inFile.read(const.ENCODE_PACKET_SIZE) # reading 1 byte at a time
    
    while byte:
        # implementing even parity method
        # sender append a 1 to make the byte with even no of 1s

        byteAscii = str(bin(ord(byte)))
        parity = 0 
        count = 0
        for i in byteAscii[2:]:
            if i == '1': 
                count += 1
       
        parity = (count %2) << 7
       # print("{}:{}".format(byteAscii,int(ord(byte))))

        outFile.write(int(ord(byte)).to_bytes(1, byteorder='big'))#storing the ascii value in binary
        outFile.write(parity.to_bytes(1, byteorder='big'))
        # print("count: ", count)
        # print("{0}: {1}".format(byte, parity))
        byte = inFile.read(const.ENCODE_PACKET_SIZE)
    
    inFile.close()
    outFile.close()

    print("VRC added to the text file!")
#####################################################################################################



###################################################################################
# CheckSum method
##################################################################################
def CHECKSUM(filename):
    print("Generating redundancy using checksum technique")
    try:
        inFile = open(filename, 'r')
    except IOError:
        sys.exit("No such file exists!")

    outFile = open("/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/CHECKSUMOutput.dat","wb")
    print("Output file \"CHECKSUMOutput.dat\" created!")

    result = 0
    byte = inFile.read(const.ENCODE_PACKET_SIZE) # reading 1 byte at a time
    while byte:
        result += ord(byte)
        outFile.write(int(ord(byte)).to_bytes(1, byteorder='big'))#storing the ascii value in binary
        byte = inFile.read(const.ENCODE_PACKET_SIZE)
    
    while True:
        if result <= 255: break
        temp = result >> 8 # this has to be added as wrap around
        result = result - (temp << 8) # last 8 bits of result
        result = result + temp

    # calculating complement
    result = 255 - result # 111,111,111,11 - result
    outFile.write(result.to_bytes(1, byteorder='big'))


    inFile.close()
    outFile.close()
    print("CheckSum added to the text file!")




###################################################################################
# LRC method
##################################################################################

def LRC(filename):

    print("Generating redundancy using LRC technique")
    try:
        inFile = open(filename, 'r')
    except IOError:
        sys.exit("No such file exists!")

    outFile = open("/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/LRCOutput.dat","wb")
    print("Output file \"LRCOutput.dat\" created!")

    LRCdata = []
    byte = inFile.read(const.ENCODE_PACKET_SIZE)
    while byte:
        LRCdata.append(ord(byte))
        outFile.write(int(ord(byte)).to_bytes(1, byteorder='big'))#storing the ascii value in binary
        byte = inFile.read(const.ENCODE_PACKET_SIZE)

    result = 0

    for i in range(8):
        count = 0
        for data in LRCdata:
            bit = data & (1 << i)
            bit = bit >> i
            count += bit
        if count % 2 == 1:
            result = result | (1<<i)
            #print(result)

    
    #print("result: ", result)
    outFile.write(result.to_bytes(1, byteorder="big"))

    inFile.close()
    outFile.close()
    print("LRC added to the text file!")



###################################################################################
# CRC method
##################################################################################

def CRC(filename, crc):
    print("Generating redundancy using CRC technique")
    try:
        inFile = open(filename, 'r')
    except IOError:
        sys.exit("No such file exists!")

    outFile = open("/home/soumalya/Desktop/MotherFolder/Assignment-5th-sem/Computer Networks/Assignment 1/CRCOutput.dat","wb")
    print("Output file \"CRCOutput.dat\" created!")

    byte = inFile.read(const.ENCODE_PACKET_SIZE) # reading 1 byte at a time
    lencrc = len(crc)
    counter = 1
    #baba = []
    while byte:

        byteAscii = str(bin(ord(byte)))[2:]
        print("Byteascii: "+byteAscii)
        outFile.write(int(ord(byte)).to_bytes(1,byteorder='big'))
        while lencrc <= len(byteAscii):
            if(byteAscii[0] == '0'): xorval = helper.xor('0'*lencrc, byteAscii[0:lencrc])
            else: xorval = helper.xor(crc, byteAscii[0:lencrc])
# 
            if(lencrc == len(byteAscii)):
                temp = xorval[1:]
                #temp1 = byteAscii+temp
                #baba.append(temp1)
                print("before left shift: "+ temp)
                byteWrite = int(temp,2)
                #print(temp)
                print("added: "+ str(bin(byteWrite))[2:])
                print("##############", counter)
                counter+=1
                outFile.write(byteWrite.to_bytes(1, byteorder='big'))
            byteAscii = xorval[1:] + byteAscii[lencrc:]
        byte = inFile.read(const.ENCODE_PACKET_SIZE)

    inFile.close()
    outFile.close()
    print("CRC added to the text file!")
    # for word in baba:
        # print(word)




if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit("No input file or method name passed!s")
    if len(sys.argv) > 3:
        sys.exit("Too many arguments passed! ")


    filename = sys.argv[-2]
    checkingType = sys.argv[-1]

    if checkingType.lower() == 'vrc': VRC(filename)
    elif checkingType.lower() == 'checksum': CHECKSUM(filename)
    elif checkingType.lower() == 'lrc': LRC(filename)
    elif checkingType.lower() == 'crc': CRC(filename, "1001")
        
    