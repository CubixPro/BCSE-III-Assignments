#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include "frame.hpp"
#include <thread>
#include<unistd.h>


int main(){
    key_t rec_key, ack_key;
    int rec_id, ack_id;

    rec_key = ftok("progfile3", 80);
    ack_key = ftok("progfile2", 70);

    rec_id = msgget(rec_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    int ack_no = 0;

    Frame f;
    struct msg f1;
    vector<struct msg> finalmsg;
    
    int rec_address;
    cin >> rec_address; 

    int current_src;
    cin >> current_src;
    while(1){
        msgrcv(rec_id, &f1, sizeof(f1), 1, 0);
        if(f1.dest != rec_address){
            msgsnd(rec_id, &f1, sizeof(f1), 0);
            sleep(3);
            continue;
        }
        if(f1.msg_sqnum < 0){
            cout << "Final Message \n";
            for(int i = 0; i < finalmsg.size() ; i++){
                string data( finalmsg[i].msg_data);
                cout << data.substr(0, SIZE) << '\n';
            }
            ack_no = 0;
            cout << "You can start using the receiver again! \n\n";
            cin  >> current_src;
            continue;
        }
        cout << "Frame " << f1.msg_sqnum <<  " received\n";
        if(f1.msg_sqnum == ack_no && checkCRC(f1))
        {
            finalmsg.push_back(f1);
            struct ack ackFrame; 
            ackFrame.msg_sqnum = ack_no;
            ackFrame.msgtype = 1;
            ackFrame.src = current_src;
            cout << "Sending Acknowledgement for Frame " << f1.msg_sqnum <<  "\n";
            msgsnd(ack_id, &ackFrame, sizeof(ackFrame), 0);
            ack_no++;
            cout << f.data << '\n';
            
        }
        /*if(f1.msg_sqnum < ack_no && checkCRC(f1)){
            struct ack ackFrame; 
            ackFrame.msg_sqnum = ack_no;
            ackFrame.msgtype = 1;
            ackFrame.src = current_src;
            cout << "Sending Acknowledgement for Frame " << f1.msg_sqnum <<  "\n";
            msgsnd(ack_id, &ackFrame, sizeof(ackFrame), 0);
            cout << f.data << '\n';
             
        }*/
        
    }
}