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
    erroneous_words = ['11010101', '10100110', '11010100', '01100110']
    return erroneous_words


def complement(bitstring):
    bitstring = bitstring.replace("0","*")
    bitstring = bitstring.replace("1","0")
    bitstring = bitstring.replace("*","1")
    return bitstring


def wrapped_sum(a, b):
    a = a[::-1]
    b = b[::-1]
    c = ""
    carry = 0
    for i in range(len(a)):
        sum = carry
        if a[i] == '1':
            sum += 1
        if b[i] == '1':
            sum += 1
        carry = 0
        if sum == 0:
            c += '0'
        elif sum == 1:
            c += '1'
        elif sum == 2:
            c += '0'
            carry = 1
        else:
            c += '1'
            carry = 1
    
    c = c[::-1]
    if carry == 0:
        return c
    else:
        x = "0" * (len(a)-1) + "1"
        return wrapped_sum(c, x)


def sender(filename):
    f = open(filename, "r")
    data = f.read()
    f.close()
    word_size = 8
    size = len(data)
    datawords = [ data[i:i+word_size] for i in range(0, size, word_size) ]
    sum = "0" * word_size
    for dataword in datawords:
        sum = wrapped_sum(sum, dataword)
    checksum = complement(sum)
    codewords = datawords
    codewords.append(checksum)
    return codewords


def noisy_channel(codewords):
    received_words = []
    for codeword in codewords:
        received_words.append(inject_random_errors(codeword))
    return received_words


def receiver(received_words):
    word_size = len(received_words[0])
    sum = "0" * word_size
    for word in received_words:
        sum = wrapped_sum(sum, word)
    sum = complement(sum)
    if sum == "0" * word_size:
        print("----NO ERROR DETECTED in received message----")
    else:
        print("----ERROR DETECTED in received message----")
    

if __name__ == '__main__':
    filename = input("Enter name of input file: ")
    receiver(noisy_channel(sender(filename)))
    