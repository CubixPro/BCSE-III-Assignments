from helper import *

def create_codeword(a, block_size, blocks, crc):
    chk = checksum(a)
    a, v = vrc(a, blocks*block_size, block_size)
    a, l = lrc(a, block_size)
    c = crc_code(a, crc)
    return  (a , chk , v , l , c)


def convert_file(file_in, file_out, block_size, blocks, crc):
    msg = open(file_in, "r")
    out = open(file_out, "w")
    text = msg.readline()
    lines = [text[i : i + block_size * blocks] for i in range(0, len(text), block_size*blocks)]
    for line in lines:
        cw, x, y, z, a = create_codeword(line, block_size, blocks, crc)
        #print(len(cw))
        out.write(cw + x + y + z + a)

    out.close()
    msg.close()