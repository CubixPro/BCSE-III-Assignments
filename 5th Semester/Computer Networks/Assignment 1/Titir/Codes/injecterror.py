import random
def adderror(file):
    f = open(file, "r")
    text = f.readline()
    l = len(text)
    random.seed()
    text = list(text)
    error = random.randrange(l)
    for i in range(error):
        e = random.randrange(l)
        text[e] = '1' 
    f.close()
    f = open(file, "w")
    text = "".join(text)
    f.write(text)
    f.close()

