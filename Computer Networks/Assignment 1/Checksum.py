def add_Checksum(codeword):
    #print("Adding redundant bits for Checksum scheme!")
    cd="00000000"
    carry="0"
    for i in range(7, -1, -1):
        if codeword[i] == '0' and codeword[i + 8] == '0':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "0"
        elif codeword[i] == '1' and codeword[i + 8] == '1':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "1"
        elif carry == "1":
            cd = cd[:i] + "0" + cd[i + 1:]
            carry = "1"
        else:
            cd = cd[:i] + "1" + cd[i + 1:]
            carry = "0"

    while True:
        for i in range(7,-1,-1):
            if carry=="0":
                break
            elif cd[i]=='1':
                cd = cd[:i] + "0" + cd[i+1:]
            else:
                cd = cd[:i] + "1" + cd[i+1:]
                carry="0"
                break

        if carry == "0":
            for i in range(8):
                if cd[i] == '0':
                    cd = cd[:i] + "1" + cd[i + 1:]
                else:
                    cd = cd[:i] + "0" + cd[i + 1:]
            return codeword + cd






def check_Checksum(codeword):
    #print("Checking for errors using the Checksum scheme!")
    cd = "00000000"
    carry = "0"
    for i in range(7, -1, -1):
        if codeword[i] == '0' and codeword[i + 8] == '0':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "0"
        elif codeword[i] == '1' and codeword[i + 8] == '1':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "1"
        elif carry == "1":
            cd = cd[:i] + "0" + cd[i + 1:]
            carry = "1"
        else:
            cd = cd[:i] + "1" + cd[i + 1:]
            carry = "0"

    while True:
        for i in range(7, -1, -1):
            if carry == "0":
                break
            elif cd[i] == '1':
                cd = cd[:i] + "0" + cd[i + 1:]
            else:
                cd = cd[:i] + "1" + cd[i + 1:]
                carry = "0"
                break
        if carry == "0":
            break

    for i in range(7, -1, -1):
        if codeword[i + 16] == '0' and cd[i] == '0':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "0"
        elif codeword[i + 16] == '1' and cd[i] == '1':
            cd = cd[:i] + carry + cd[i + 1:]
            carry = "1"
        elif carry == "1":
            cd = cd[:i] + "0" + cd[i + 1:]
            carry = "1"
        else:
            cd = cd[:i] + "1" + cd[i + 1:]
            carry = "0"

    while True:
        for i in range(7, -1, -1):
            if carry == "0":
                break
            elif cd[i] == '1':
                cd = cd[:i] + "0" + cd[i + 1:]
            else:
                cd = cd[:i] + "1" + cd[i + 1:]
                carry = "0"
                break
        if carry == "0":
            break

    for i in range(8):
        if cd[i]=='0':
            print("Error is detected using Checksum scheme!")
            return False
    print("No error is detected using Checksum scheme!")
    return True