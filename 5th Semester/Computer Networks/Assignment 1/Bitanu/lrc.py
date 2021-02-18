import random


def inject_random_errors(word):
    word_size = len(word)
    num_errors = random.randint(0, word_size//2)
    indices = random.choices(range(word_size), k=num_errors)
    erroneous_word = ''
    for i in range(word_size):
        if i in indices:
            if word[i] == '0':
                erroneous_word += '1'
            else:
                erroneous_word += '0'
        else:
            erroneous_word += word[i]
    return erroneous_word


def hardcode_errors():
    erroneous_words = ['11000100', '10001011', '01001001', '00000110']
    return erroneous_words


def sender(filename):    
    f = open(filename, "r")
    data = f.read()
    f.close()
    word_size = 8
    size = len(data)
    datawords = [ data[i:i+word_size] for i in range(0, size, word_size) ]
    parity_bits = ''
    for i in range(word_size):
        parity = 0
        for dataword in datawords:
            if dataword[i] == '1':
                parity += 1
        if parity % 2 == 0:
            parity_bits += '0'
        else:
            parity_bits += '1'
    codewords = datawords
    codewords.append(parity_bits)
    return codewords
    

def noisy_channel(codewords):
    received_words = []
    for codeword in codewords:
        received_words.append(inject_random_errors(codeword))
    return received_words


def receiver(received_words):
    word_size = len(received_words[0])
    flag = 0
    for i in range(word_size):
        parity = 0
        for word in received_words:
            if word[i] == '1':
                parity += 1
        if parity % 2 == 1:
            flag = 1
    if flag == 0:
        print("----NO ERROR DETECTED in received message----")
    else:
        print("----ERROR DETECTED in received message----")
            

if __name__ == '__main__':
    filename = input("Enter name of input file: ")
    receiver(noisy_channel(sender(filename)))