#include <bits/stdc++.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "frame.hpp"
#include <thread>
#include <unistd.h>
#include <chrono>

#define CRC "1101"
using namespace std;

class Exception{
    public:
    int seqN;
    Exception(int n){
        seqN = n;
    }
};
int main()
{
    key_t msg_key, ack_key;
    int msg_id, ack_id;// timeout = 3;

    msg_key = ftok("progfile1", 65);
    ack_key = ftok("progfile2", 70);

    msg_id = msgget(msg_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    int m = 2;
    int sn = 0, sf = 0, sw = pow(2, m) - 1;

    int totalFrames;

    cin >> totalFrames;
    
    int timeout[sw];
    for(int i = 0 ; i < sw ; i++){
        timeout[i] = 0;
    }

    struct msg frames[sw];


    while(sf != totalFrames){
        try{
            if((sn - sf) < sw && sn != totalFrames){
                struct msg frame;
                frame.msgtype = 1;
                frame.msg_sqnum = sn;
                for(int i = 0 ; i < SIZE ; i ++){
                    frame.msg_data[i] = (char)(rand()%26 + 97);
                }
                addCRC(&frame);
                cout << "Sending Frame : " << sf << " " << frame.msg_data << '\n';
                frames[sn%sw] = frame;
                msgsnd(msg_id, &frame, sizeof(frame), 0);
                sn = sn + 1;
                
            }
            struct acknowledgement ackFrame;
            int ack_rec = msgrcv(ack_id, &ackFrame, sizeof(ackFrame), 1, 1 | IPC_NOWAIT);
            while(ack_rec >= 0){
                if (ackFrame.msg_type == -1)//nak
                {
                    cout << "Resending Frame " << ackFrame.msg_sqnum << '\n';
                    msgsnd(msg_key, &frames[(ackFrame.msg_sqnum)%sw], sizeof(struct msg), 0);
                    timeout[ackFrame.msg_sqnum%sw] = 0;
                }
                else if(ackFrame.msg_type == 0 )
                 while (sf <= ackFrame.msg_sqnum){
                    cout << "Received Acknowledgement for Frame " << sf << '\n';
                    timeout[sf%sw] = 0;
                    sf = sf + 1;
                }
            }
            for(int i = sf ; i <sn ;i++){
                timeout[i%sw]++;
                if(timeout[i%sw] > 100000000)
                {
                    throw Exception(i);
                }
            }
        }
        catch(Exception e){
           cout << "Timeout of Frame " << e.seqN << '\n'; 
           timeout[e.seqN] = 0;
           msgsnd(msg_id, &frames[e.seqN], sizeof(struct msg), 0);
           sleep(3);
        }
    }


}