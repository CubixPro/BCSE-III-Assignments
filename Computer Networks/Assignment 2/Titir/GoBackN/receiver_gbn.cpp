#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "frame.hpp"
#include <thread>
#include <unistd.h>

#define CRC "1101"


int main(){
    key_t rec_key, ack_key;
    int rec_id, ack_id;

    rec_key = ftok("progfile3", 80);
    ack_key = ftok("progfile2", 70);

    rec_id = msgget(rec_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    vector<struct msg> finalmsg;
    int rn = 0;
    struct msg f;
    int sw = 3;
    while(true){
        int p = msgrcv(rec_id, &f, sizeof(f), 1, 0);
        if(p >= 0 && f.msg_sqnum < 0){
            cout << "Final Message \n";
            for(int i = 0; i < finalmsg.size() ; i++){
                string data( finalmsg[i].msg_data);
                cout << data.substr(0, SIZE) << '\n';
            }
            rn = 0;
            cout << "You can start using the receiver again! \n\n";
            //cin  >> current_src;
            continue;
        }
        if(p >= 0 && f.msg_sqnum == rn && checkCRC(f)){
            //rn = rn + 1;
            cout << "Received Frame " << rn << '\n';
            finalmsg.push_back(f);
            struct ack ackFrame;
            ackFrame.msg_sqnum = rn;
            ackFrame.msgtype = 1;
            cout << "Sending Acknowledgement for Frame " << rn << "\n \n";
            msgsnd(ack_id, &ackFrame, sizeof(ackFrame), 0);
            rn = (rn + 1);
        } 
    }
}