
def getNextPowerof2(num):
    power = 1
    while(power < num):
        power *= 2
    return power


def buildWalshTable(length, i1,i2, j1,j2, isComplement):
    if length == 2:
        if not isComplement:
            wTable[i1][j1] = 1
            wTable[i1][j2] = 1
            wTable[i2][j1] = 1
            wTable[i2][j2] = -1
        else:
            wTable[i1][j1] = -1
            wTable[i1][j2] = -1
            wTable[i2][j1] = -1
            wTable[i2][j2] = 1
        
        return
    
    midi = (i1+i2)//2
    midj = (j1+j2)//2

    buildWalshTable(length/2, i1, midi, j1, midj, isComplement)
    buildWalshTable(length/2, i1, midi, midj+1, j2, isComplement)
    buildWalshTable(length/2, midi+1, i2, j1, midj, isComplement)
    buildWalshTable(length/2, midi+1, i2, midj+1, j2, not isComplement)

    return


if __name__ == "__main__":

    num_stations = 5
    num = getNextPowerof2(num_stations)
    wTable = [[0 for i in range(num)] for j in range(num)]

    buildWalshTable(num, 0, num - 1, 0, num - 1, False)
    print(wTable)
    print(len(wTable[0]))
    