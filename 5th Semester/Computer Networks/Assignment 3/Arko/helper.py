def checkSum(segData):

    total = 0
    data = [segData[i: i+32] for i in range(0, len(segData), 32)]
    for y in data:
        total += int(y,2)
        if total >= 4294967295:
            total -= 4294967295
    
    ckSum = 4294967295 - total
    ckSumBits = '{0:032b}'.format(ckSum)
    return ckSumBits

def checkError(segData):

    total = 0
    data = [segData[i: i+32] for i in range(0, len(segData), 32)]
    for y in data:
        total += int(y,2)
        if total >= 4294967295:
            total -= 4294967295
    #print("Total Checksum:"+str(total))
    return 1 if total == 0 else 0