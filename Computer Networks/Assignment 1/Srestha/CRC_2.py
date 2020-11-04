def division(dataword,poly):
    dataword=dataword + "0"*(len(poly)-1)
    while len(dataword)>=len(poly):
        if dataword[0]=='1':
            for i in range(len(poly)):
                if dataword[i]==poly[i]:
                    dataword = dataword[:i] + "0" + dataword[i + 1:]
                else:
                    dataword = dataword[:i] + "0" + dataword[i + 1:]
        dataword= dataword[1:]
    return dataword



def add_CRC(codeword):
    #print("Adding redundant bits for CRC scheme!")
    poly="100110001"
    rem= division(codeword[:16],poly)
    codeword=codeword+rem
    return codeword


def check_CRC(codeword):
    #print("Checking for errors using the CRC scheme!")
    poly="100110001"
    rem= division(codeword,poly)
    for i in range(len(rem)):
        if rem[i]=='1':
            print("Error is detected using CRC scheme!")
            return False
    print("No error is detected using CRC scheme!")
    return True