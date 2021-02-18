from helper import *

def vrc_check(text, frame_size, block_size):
    blocks = frame_size/block_size
    msg = text[0: frame_size]
    v = text[frame_size+ 2*block_size : frame_size+ 2*block_size+ int(blocks)]
    v1 = vrc(msg, frame_size, block_size)
    for i in range(len(v1)):
        if(v[i] != v1[i]):
            return False
    return True

def lrc_check(text, frame_size, block_size):
    msg = text[0: frame_size]
    l = text[frame_size+ block_size : frame_size+ 2*block_size]
    l1 = lrc(msg, block_size)
    for i in range(len(l1)):
        if(l[i] != l1[i]):
            return False
    return True

def checksum_check(text, frame_size, block_size):
    msg = text[0: frame_size]
    chk = text[frame_size : frame_size+ block_size]
    chk1 = checksum(msg, frame_size, block_size)
    for i in range(len(chk1)):
        if(chk[i] != chk1[i]):
            return False
    return True

def crc_check(text, frame_size, block_size, crc_poly):
    blocks = frame_size/block_size
    msg = text[0: frame_size]
    c = text[frame_size+ 2*block_size+ int(blocks): ]
    c1 = crc_code(msg, crc_poly)
    for i in range(len(c1)):
        if(c[i] != c1[i]):
            return False
    return True