import random
def inject_error(fileName):
    fileptr = open(fileName, "r")
    text = fileptr.readline()
    length = len(text)

    random.seed()

    text = list(text)

    num = int(input("Enter the number of errors you want to inject:  "))

    for i in range (num):
        pos = random.randrange(length)
        if(text[pos] == '0'):
            text[pos] = '1'
        else:
            text[pos] = '0'
    
    fileptr.close()

    fileptr = open(fileName, "w")
    text = "".join(text)
    fileptr.write(text)
    fileptr.close()


    