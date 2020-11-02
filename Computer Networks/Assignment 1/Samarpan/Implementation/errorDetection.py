import packetCreator

def detect_error(outFile, crcCode, blockSize, blocks):
    test_vrc = True
    test_lrc = True
    test_chksum = True
    test_crc = True

    total_length = blockSize*blocks + (len(crcCode)-1) + blockSize + blocks + 1
    fileptr = open(outFile, "r")
    chunk = fileptr.readline()

    lines = [chunk[i: i + total_length] for i in range(0, len(chunk), total_length)]

    for l in lines:
        data_part = l[:blockSize*blocks]
        chksum = l[blockSize*blocks]
        vrc = l[blockSize*blocks + 1 : blockSize*blocks + 1 + blocks]
        lrc = l[blockSize*blocks + 1 + blocks : blockSize*blocks + 1 + blocks + blockSize]
        crc = l[blockSize*blocks + 1 + blocks + blockSize:]

        temp, tvrc, tlrc, tchksum, tcrc = packetCreator.create_packet(data_part, blockSize, blocks, crcCode)

        if(chksum != tchksum):
            test_chksum = False
        
        if(vrc != tvrc):
            test_vrc = False

        if(lrc != tlrc):
            test_lrc = False
        
        if(crc != tcrc):
            test_crc = False

    fileptr.close()
    return test_vrc, test_lrc, test_chksum, test_crc

    