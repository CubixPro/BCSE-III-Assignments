
from create_packet_all import *

def detect_error(packet, crc, block_size, blocks):
    check_crc = True
    check_lrc = True
    check_vrc = True
    check_cs = True
    
    countneither = 0
    total_fs = block_size*blocks + (len(crc) - 1) + block_size + blocks + 1
    inp = open(packet, "r")
    text = inp.readline()
    lines = [text[i: i + total_fs] for i in range(0, len(text), total_fs)]
    for line in lines:
        data_w = line[:block_size*blocks]
        chk = line[block_size*blocks]
        v = line[block_size*blocks + 1 : block_size*blocks + 1 + blocks]
        l = line[block_size*blocks + 1 + blocks : block_size*blocks + 1 + blocks + block_size]
        c = line[block_size*blocks + 1 + blocks + block_size:]
        x, y, z, a, b = create_codeword(data_w, block_size, blocks, crc)
        if chk != y:
            check_cs = False
        if z != v:
            check_vrc = False
        if l != a:
            check_lrc = False
        if b != c:
            check_crc = False
        
    
    return check_crc, check_cs, check_lrc, check_vrc