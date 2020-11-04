from helper import *

def create_codeword(text, block_size, blocks, crc):
    chk = checksum(text, blocks*block_size, block_size)
    v = vrc(text, blocks*block_size, block_size)
    l = lrc(text, block_size)
    c = crc_code(text, crc)
    return  (chk, v, l, c)


def convert_file(file_in, file_out, block_size, blocks, crc):
    msg = open(file_in, "r")
    out = open(file_out, "w")
    text = msg.readline()
    chk, v, l, c = create_codeword(text, block_size, blocks, crc)
    msg.close()
    print("The vcr code is: ", v)
    print("The lcr code is: ", l)
    print("The check sum is: ", chk)
    print("The crc code is: ", c)
    out.write(text + chk + l + v + c)
    out.close()