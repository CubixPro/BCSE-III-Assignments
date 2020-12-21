def checkSum(segData):
    # returnnig string

    total = 0
    #print(len(segData))
    data = [segData[i: i+16] for i in range(0, len(segData), 16)]
    for y in data:
        total += int(y,2)
        if total >= 65535:
            total -= 65535
    
    
    ckSum = 65535 - total
    ckSumBits = '{0:016b}'.format(ckSum)
    return ckSumBits

def checkError(segData):
    total = 0
    data = [segData[i: i+16] for i in range(0, len(segData), 16)]
    #print(data)
    for y in data:
        total += int(y,2)
        if total >= 65535:
            total -= 65535
    #print("Total Checksum:"+str(total))
    return 1 if total == 0 else 0
    
