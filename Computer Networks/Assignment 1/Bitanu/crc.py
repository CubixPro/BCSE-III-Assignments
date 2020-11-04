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
    erroneous_words = ['010100000010']
    return erroneous_words

    
def xor(a, b): 
    result = ''
    for i in range(1, len(b)): 
        if a[i] == b[i]: 
            result += '0' 
        else: 
            result += '1' 
    return result 

  
def mod2division(dividend, divisor): 
    divisor_size = len(divisor) 
    temp = dividend[0:divisor_size] 
  
    while divisor_size < len(dividend): 
        if temp[0] == '1':   
            temp = xor(divisor, temp) + dividend[divisor_size]   
        else:   
            temp = xor('0'*divisor_size, temp) + dividend[divisor_size]  
        divisor_size += 1
   
    if temp[0] == '1': 
        temp = xor(divisor, temp) 
    else: 
        temp = xor('0'*divisor_size, temp) 
  
    remainder = temp 
    return remainder 


def sender(filename):    
    f = open(filename, "r")
    data = f.read()
    f.close()
    word_size = 8
    size = len(data)
    datawords = [ data[i:i+word_size] for i in range(0, size, word_size) ]
    divisor = "10011"
    redundant_bits = 4
    codewords = []
    for dataword in datawords:
       appended_dataword = dataword + '0'*(redundant_bits) 
       remainder = mod2division(appended_dataword, divisor)
       codeword = dataword + remainder 
       codewords.append(codeword)
    return codewords

    
def noisy_channel(codewords):
    received_words = []
    for codeword in codewords:
        received_words.append(inject_random_errors(codeword))
    return received_words


def receiver(received_words):
    divisor = "10011"
    flag = 0
    for idx, word in enumerate(received_words,1):
        remainder = mod2division(word, divisor)
        if remainder != "0" * (len(divisor)-1):
            flag = 1
    if flag == 0:
        print("----NO ERROR DETECTED in received message----")
    else:
        print("----ERROR DETECTED in received message----")
            

if __name__ == '__main__':
    filename = input("Enter name of input file: ")
    receiver(noisy_channel(sender(filename)))




















