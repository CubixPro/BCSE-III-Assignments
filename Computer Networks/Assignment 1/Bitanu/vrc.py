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
    erroneous_words = ['010100001']
    return erroneous_words


def sender(filename):    
    f = open(filename, "r")
    data = f.read()
    f.close()
    word_size = 8
    size = len(data)
    datawords = [ data[i:i+word_size] for i in range(0, size, word_size) ]
    codewords = []
    for dataword in datawords:
        parity = 0
        for bit in dataword:
            if bit == '1':
                parity += 1
        if parity % 2 == 0:
            codewords.append(dataword + '0')
        else:
            codewords.append(dataword + '1')
    return codewords


def noisy_channel(codewords):
    received_words = []
    for codeword in codewords:
        received_words.append(inject_random_errors(codeword))
    return received_words


def receiver(received_words):
    flag = 0
    for idx, word in enumerate(received_words, 1):
        parity = 0
        for bit in word:
            if bit == '1':
                parity += 1
        if parity % 2 != 0:
            flag = 1
    if flag == 0:
        print("----NO ERROR DETECTED in received message----")
    else:
        print("----ERROR DETECTED in received message----")


if __name__ == '__main__':
    filename = input("Enter name of input file: ")
    receiver(noisy_channel(sender(filename)))