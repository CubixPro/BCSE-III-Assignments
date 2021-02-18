import addErrorDetection

def create_packet(line, blockSize, blockNo, crcCode):
    line, v = addErrorDetection.VRC(line, blockSize*blockNo, blockSize)
    line, l = addErrorDetection.LRC(line, blockSize)
    chksum = addErrorDetection.CHECKSUM(line)
    c = addErrorDetection.CRC(line, crcCode)

    return (line, v, l, chksum, c)


def convert_message(fileIn, fileOut, blockSize, blockNo, crcCode):
    message = open(fileIn, "r")
    output = open(fileOut, "w")
    text = message.readline()
    lines = [text[i: i + blockSize * blockNo] for i in range(0, len(text), blockSize*blockNo)]

    for l in lines:
        original, vrc, lrc, checksum, crc = create_packet(l, blockSize, blockNo, crcCode)
        output.write(original + checksum + vrc + lrc + crc)
    
    message.close()
    output.close()
