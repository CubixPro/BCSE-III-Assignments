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
        if(lencrc == len(str)):
            return xorval[1:]
        str = xorval[1:] + str[lencrc:]

def xorsum(a):
    while len(a) != 1:
        a = xor(a[0], a[1]) + a[2:]
    return a

def lrc(a, block_length):

    lines = [a[i: i + block_length] for i in range(0, len(a), block_length)]
    lrc = '0' * block_length
    for line in lines:
        lrc = xor(lrc, line)
    return lrc

def vrc(a, frame_size, block_length):

    lines = [a[i: i + block_length] for i in range(0, len(a), block_length)]
    vrc = ''
    for line in lines:
        vrc = vrc + xorsum(line)
    return vrc 

def checksum(a, frame_size, block_length):

    lines = [a[i: i + block_length] for i in range(0, len(a), block_length)]
    c_sum = []
    for line in lines:
        c_sum.append(int(line, 2))
    while len(c_sum) != 1:
        if((c_sum[0] + c_sum[1]) - pow(2, block_length) >= 0):
            c_sum = [(c_sum[0] + c_sum[1] - pow(2, block_length) +1)] + c_sum[2: ]
        else:
            c_sum = [(c_sum[0] + c_sum[1])] + c_sum[2: ]

    res = bin(c_sum[0]).replace("0b","")
    new_res = ''
    while(len(new_res) != block_length- len(res)):
        new_res += '0'
    return (new_res + res)
