import random
def adderror(file_out, error, frame_size):
    f = open(file_out, "r")
    text = f.readline()
    text = list(text)
    l = len(text)
    for i in range(error):
        e = random.randrange(frame_size)
        if(text[e] == '0'):
            text[e] = 1
        else:
            text[e] = 0
    f.close()
    str1 = ''
    for ele in text:
        str1 += str(ele)
    f = open(file_out, "w")
    f.write(str1)
    f.close()