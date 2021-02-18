def xor(a, b):
    val = []
    for i in range(len(b)):
        if(a[i] == b[i]):
            val.append('0')
        else:
            val.append('1')
    
    return ''.join(val)


def crc_code(str, crc):
    
    lencrc = len(crc)
    
    while lencrc <= len(str):
        if(str[0] == '0'):
            xorval = xor('0'*lencrc, str[0:lencrc])
        else:
            xorval = xor(crc, str[0:lencrc])
        #print(xorval)
        if(lencrc == len(str)):
            return xorval[1:]
        str = xorval[1:] + str[lencrc:]

def checksum(a):
    while len(a) != 1:
        a = xor(a[0], a[1]) + a[2:]

    return a


def lrc(a, length):
    if len(a)%length != 0:
        a = a + '0'*(length - len(a)%length)
    lines = [a[i: i + length] for i in range(0, len(a), length)]
    lrc = '0' * length
    for line in lines:
        lrc = xor(lrc, line)
    return a, lrc

def vrc(a, frame_size, block_length):
    if len(a)%frame_size != 0:
        a = a + '0'*(frame_size - len(a)%frame_size)
    lines = [a[i: i + block_length] for i in range(0, len(a), block_length)]
    vrc = ''
    for line in lines:
        vrc = vrc + checksum(line)
    return a, vrc 

  