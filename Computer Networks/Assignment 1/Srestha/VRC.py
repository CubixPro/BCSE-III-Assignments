def add_VRC(codeword):
    #print("Adding redundant bits for VRC scheme!")
    for i in range(8):
        if codeword[i]=='0' and codeword[i+8]=='0':
            codeword=codeword+"0"
        elif codeword[i]=='1' and codeword[i+8]=='1':
            codeword=codeword+"0"
        else:
            codeword=codeword+"1"
    return codeword




def check_VRC(codeword):
    #print("Checking for errors using the VRC scheme!")
    for i in range(8):
        if codeword[i]=='0' and codeword[i+8]=='0' and codeword[i+16]=='1':
            print("Error is detected using VRC scheme!")
            return False
        elif codeword[i]=='1' and codeword[i+8]=='1' and codeword[i+16]=='1':
            print("Error is detected using VRC scheme!")
            return False
        elif codeword[i]=='0' and codeword[i+8]=='1' and codeword[i+16]=='0':
            print("Error is detected using VRC scheme!")
            return False
        elif codeword[i]=='1' and codeword[i+8]=='0' and codeword[i+16]=='0':
            print("Error is detected using VRC scheme!")
            return False
    print("No error is detected using VRC scheme!")
    return True