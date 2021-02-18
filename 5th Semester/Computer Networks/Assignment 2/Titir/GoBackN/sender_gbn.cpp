#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "frame.hpp"
#include <thread>
#include <unistd.h>
#include <chrono>

#define CRC "1101"
using namespace std;
void timeout(int value){
    while(value-- != 0);
    throw "Timeout!";
}

int main()
{
    key_t msg_key, ack_key;
    int msg_id, ack_id;// timeout = 3;

    msg_key = ftok("progfile1", 60);
    ack_key = ftok("progfile2", 70);

    msg_id = msgget(msg_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    bool resend_flag = false;

    //Frame tempf;

    int i = 0;

    string toBeSend;
    //int timeout;
    //cin >> toBeSend;
    int m = 2;
    int sf = 0;
    int sn = 0;
    int sw = pow(2, m) - 1;
    struct msg frames[sw];
    bool cansend = true;
    //string toBeSend;
    //cin >> toBeSend;
    //int i = 0;
    int totalframes;
    cin >> totalframes;
    //thread threads[sw];
    //Timer *timers = (Timer *)malloc(sizeof(Timer) * sw);
    /*for (int i = 0; i < sw; i++)
    {
        timers[i] = Timer(5);
    }*/
    int timeout[5];
    for (int i = 0 ; i < 5 ; i++){
        timeout[i] = 0;
    } 
    while (totalframes != sf)
    {

        try
        {
            while (totalframes != sf)
            {
                if ((sn - sf) < sw && sn != totalframes)
                {

                    struct msg f;
                    //string data;
                    //cin >> data;
                    //f.makeFrame(data, CRC);
                    //f.setSeqN( sn);
                    f.msgtype = 1;
                    f.msg_sqnum = sn;
                    for (int i = 0; i < SIZE; i++)
                    {
                        f.msg_data[i] = (char)(rand() % 2 + 48);
                    }
                    addCRC(&f);
                    frames[sn % sw] = f;
                    //timers[sn % sw].start();
                    //thread t(timeout, 10000000);
                    cout << "Sending Frame : " << f.msg_sqnum << " "<< f.msg_data << '\n';
                    msgsnd(msg_id, &f, sizeof(f), 0);
                    sn = sn + 1;
                }

                struct ack ackFrame;
                int ack_rec = msgrcv(ack_id, &ackFrame, sizeof(ackFrame), 1, IPC_NOWAIT);
                
                while (ack_rec >= 0 && ackFrame.msg_sqnum >= sf && ackFrame.msg_sqnum < sn)
                {
                    int tempf = sf;
                    while (tempf <= ackFrame.msg_sqnum)
                    {
                        // frames[tempf%sw] = nullptr;
                        //timers[tempf % sw].end();
                        //sleep(1);
                        //timers[tempf % sw].start();
                        cout << "Received Acknowledgement for Frame " << sf << '\n';
                        timeout[tempf%sw] = 0;
                        tempf++;
                        sf++;
                    }
                    ack_rec = msgrcv(ack_id, &(ackFrame), sizeof(ackFrame), 1, IPC_NOWAIT);
                }
                for(int i = sf ; i < sn ; i++){
                    timeout[i]++;
                    if(timeout[i] > 10000000){
                        throw "Timeout!";
                    }
                } 
            }
        }
        catch (...)
        {
            //timeout
            
            int tempf = sf;
            while (tempf < sn)
            {
                cout << "Resending Frame : " << frames[tempf % sw].msg_sqnum  << '\n';
                msgsnd(msg_id, &frames[tempf % sw], sizeof(frames[tempf % sw]), 0);
                tempf++;
                //timeout[tempf%sw] = 0;
            }
            for(int i = 0 ; i < sw ; i++){
                timeout[i] = 0;
            }
            sleep(5);
        }
    }
    struct msg f;
    f.msgtype = 1;
    f.msg_sqnum = -1;
    
    msgsnd(msg_id, &f, sizeof(f), 0);
}


//change the while loop
//change the ack
