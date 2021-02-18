def add_LRC(codeword):
    #print("Adding redundant bits for LRC scheme!")
    count=0
    for i in range(16):
        if codeword[i]=='1':
            count=count+1
    if count%2==0:
        codeword=codeword+"0"
    else:
        codeword=codeword+"1"
    return codeword




def check_LRC(codeword):
    #print("Checking for errors using the LRC scheme!")
    count = 0
    for i in range(16):
        if codeword[i] == '1':
            count = count + 1
    if count%2==0 and codeword[16]=='0':
        print("No error detected using LRC scheme!")
        return True
    elif count%2==1 and codeword[16]=='1':
        print("No error detected using LRC scheme!")
        return True
    else:
        print("Error is detected using LRC scheme!")
        return False
