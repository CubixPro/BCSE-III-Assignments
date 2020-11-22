#include <bits/stdc++.h>
#include <cstring>
#include <ctime>
#define SIZE 6 
#define CRC_VAL "1101"
#define CRC_SIZE 3
using namespace std;

struct msg{
    long int msgtype;
    char msg_data[SIZE];
    char crc[CRC_SIZE]; 
    int msg_sqnum;
};

struct ack{
    long int msgtype;
    int msg_sqnum;
};


struct acknowledgement{
    long int msgtype;
    int msg_sqnum;
    int msg_type;//1 = ACK 0 = NCK
};




class Frame
{
    public:
        string data;
        string crc;
        int seqN;

    private:
        string toBin(long long int num)
        {
            string bin = "";
            while (num)
            {
                if (num & 1)
                    bin = "1" + bin;
                else
                    bin = "0" + bin;
                num = num >> 1;
            }
            return bin;
        }
        long long int toDec(string bin)
        {
            long long int num = 0;
            for (int i = 0; i < bin.length(); i++)
            {
                if (bin.at(i) == '1')
                    num += 1 << (bin.length() - i - 1);
            }
            return num;
        }
        void CRC(string dataword, string generator)
        {
            int l_gen = generator.length();
            long long int gen = toDec(generator);

            long long int dword = toDec(dataword);

            // append 0s to dividend
            long long int dividend = dword << (l_gen - 1);

            // shft specifies the no. of least
            // significant bits not being XORed
            int shft = (int)ceill(log2l(dividend + 1)) - l_gen;
            long long int rem;

            while ((dividend >= gen) || (shft >= 0))
            {

                // bitwise XOR the MSBs of dividend with generator
                // replace the operated MSBs from the dividend with
                // remainder generated
                rem = (dividend >> shft) ^ gen;
                dividend = (dividend & ((1 << shft) - 1)) | (rem << shft);

                // change shft variable
                shft = (int)ceill(log2l(dividend + 1)) - l_gen;
            }

            // finally, AND the initial dividend with the remainder (=dividend)
            long long int codeword = (dword << (l_gen - 1)) | dividend;
            crc = toBin(codeword);    
        }

    public:
        void makeFrame(string dataw, string crcw){
            data = dataw;
            CRC(data, crcw);
        }
        void setSeqN(int num){
            seqN = num;
        }
    
};



class Acknowledgement{
    public: 
    time_t t;
    int seqN;
    public: Acknowledgement(int n){
        t = time(0);
        seqN = n;
    }

};


void addCRC(struct msg* frame){
    string data( frame->msg_data);
    data = data.substr(0, SIZE);
    Frame f;
    f.makeFrame(data, CRC_VAL);
    string crc_val = f.crc.substr(f.crc.length() - CRC_SIZE );
    strcpy(frame->crc, crc_val.c_str()); 
}

bool checkCRC(struct msg frame){
    struct msg frame2 = frame;
    addCRC(&frame2);
    if(strcmp(frame.crc, frame2.crc) == 0){
        return true;
    } 
    else{
        return false;
    }
}


//figure out error