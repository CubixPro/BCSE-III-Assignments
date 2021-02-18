import random

def inject_error(codeword):
    length= len(codeword)
    #random.seed()
    no_of_errors= random.randrange(0,25,1)
    for i in range(no_of_errors):
        j = random.randrange(0,len(codeword),1)
        if codeword[j]=='0':
            codeword=codeword[:j]+"1"+codeword[j+1:]
        else:
            codeword = codeword[:j] + "0" + codeword[j + 1:]
    return codeword