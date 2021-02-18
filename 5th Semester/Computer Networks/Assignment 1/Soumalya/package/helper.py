import os

def xor(a,b):
    val = []
    for i in range(len(b)):
        if a[i] == b[i]:
            val.append("0")
        else: val.append("1")
    return "".join(val)


def byteToString(byte):
    length = len(byte)
    byte = byte.decode('utf-8')
    
    return ''.join(format(ord(i),'b') for i in byte)

def fileSize(filename):
    file = os.stat(filename)
    print("File size in bytes: ", file.st_size)

def checkParity(res):
    count = 0
    for i in range(len(res)):
        if res[i] == '1': count+=1
    
    if count%2 == 1: return False
    else: return True

def pad(redun, lencrc):
    # pad the redundant string with 0s to make it lencrc-1 length
    lenredun = len(redun)
    if(lenredun < lencrc-1):
        redun = '0'*(lencrc-1-lenredun) + redun
    
    return redun