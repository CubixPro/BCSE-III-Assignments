from CRC import add_CRC,check_CRC
from VRC import *
from Checksum import *
from LRC import *
from Errors import *




def sender(cd):
    #print("Calling function to add redundant bits for VRC scheme!")
    cd = add_VRC(cd)
    #print("The codeword is- " + cd)

    #print("Calling function to add redundant bits for Checksum scheme!")
    cd = add_Checksum(cd)
    #print("The codeword is- " + cd)

    #print("Calling function to add redundant bits for LRC scheme!")
    cd= add_LRC(cd)
    #print("The codeword is- "+cd)

    #print("Calling function to add redundant bits for CRC scheme!")
    cd = add_CRC(cd)
    #print("The codeword is- " + cd)
    return cd





def channel(cd):
    ch= input("Do you want to insert errors in the datapacket? Y/N")
    if ch=="N":
        return cd
    else:
        cd = inject_error(cd)
        return cd





def decode_dataword(word):
    str_data = ""
    for i in range(len(word)):
        if word[i]=='1':
            break
    word=word[i:]
    for i in range(0, len(word), 7):
        temp = word[i:i + 7]
        decimal = int(temp,2)
        str_data = str_data + chr(decimal)
    print("The characters decoded-"+str_data)
    file2= open("ReceiverFile.txt","a")
    file2.write(str_data)
    file2.close()






def reciever(cd):
    # print("Calling function to check for error using VRC scheme!")
    correct1 = check_VRC(cd)
    code = cd[:16] + cd[24:]
    cd = code

    # print("Calling function to check for error using Checksum scheme!")
    correct2 = check_Checksum(cd)
    code = cd[:16] + cd[24:]
    cd = code

    # print("Calling function to check for error using LRC scheme!")
    correct3 = check_LRC(cd)
    code = cd[:16] + cd[17:]
    cd = code

    # print("Calling function to check for error using CRC scheme!")
    correct4 = check_CRC(cd)
    cd = cd[:16]

    if correct1 and correct2 and correct3 and correct4:
        print("No error is detected in recieved data packet! Transmission successful!")
        decode_dataword(cd)
        return True
    else:
        print("Error is detected in recieved data packet! Requesting retransmission!")
        return False





def create_dataword(data):
    dataword = str(''.join(format(ord(i), 'b') for i in data))
    for i in range(8-(len(dataword)%8)):
        dataword= "0"+dataword
    while 16>len(dataword):
        dataword= dataword + "0"
    return dataword





filename= input("Enter file name: ")
file1= open(filename,"r")
count=0
while 1:
    data = file1.read(2)
    if not data:
        break

    #print("The characters read from file is-"+ data)
    correct= False
    while correct==False:
        dataword = create_dataword(data)
        #print("The dataword- " + dataword)
        codeword = sender(dataword)
        print("The codeword sent from the sender side-" + codeword)
        codeword = channel(codeword)
        print("The codeword recieved at the reciever side-" + codeword)
        correct = reciever(codeword)

print("File transfer complete!")
file1.close()
