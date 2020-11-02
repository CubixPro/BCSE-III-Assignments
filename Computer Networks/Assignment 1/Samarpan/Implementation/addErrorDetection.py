#Basic XOR Logic
def XOR(a1, a2):
    ans = []
    for i in range(len(a2)):
        if(a1[i] == a2[i]):
            ans.append('0')
        else:
            ans.append('1')
    
    return ''.join(ans)

#Checksum Logic
def CHECKSUM(line):
    while len(line) != 1:
        line = XOR(line[0], line[1]) + line[2:]

    return line

#LRC Logic
def LRC(line, length):
    if len(line)%length != 0:
        line = line + '0'*(length - len(line)%length)
    lines = [line[i: i + length] for i in range(0, len(line), length)]
    lrc = '0' * length
    for l in lines:
        lrc = XOR(lrc, l)

    return line, lrc


#VRC Logic
def VRC(line, frameSize, blockLength):
    if len(line)%frameSize != 0:
        line = line + '0'*(frameSize - len(line)%frameSize)
    lines = [line[i: i + blockLength] for i in range(0, len(line), blockLength)]
    vrc = ''
    for l in lines:
        vrc = vrc + CHECKSUM(l)

    return line, vrc

#CRC Logic
def CRC(line, crcCode):
    length = len(crcCode)

    while length <= len(line):
        if(line[0] == '0'):
            val = XOR('0'*length, line[0:length])
        else:
            val = XOR(crcCode, line[0:length])
        
        if(length == len(line)):
            return val[1:]

        line = val[1:] + line[length:]