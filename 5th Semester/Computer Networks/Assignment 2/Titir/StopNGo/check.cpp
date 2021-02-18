


#include "frame.hpp"
#include <cstdlib>
#include <cstring>


int main(){
    struct msg f;
    string str = "101100";
    string crc = "001";
    strcpy(f.msg_data, str.c_str());
    strcpy(f.crc, crc.c_str());
    cout << checkCRC(f) << '\n';
}