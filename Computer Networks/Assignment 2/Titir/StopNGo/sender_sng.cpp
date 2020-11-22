#define _OPEN_SYS_TIMED_EXT 1
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "frame.hpp"
#include <time.h>
#include <unistd.h>

#define CRC "1101"

int main()
{
    key_t msg_key, ack_key;
    int msg_id, ack_id, timeout = 3;

    msg_key = ftok("progfile1", 60);
    ack_key = ftok("progfile2", 70);

    msg_id = msgget(msg_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    bool resend_flag = false;

    struct msg tempf;

    int i = 0;

    //string toBeSend;

    //cin >> toBeSend;

    int n; //how many frames you want to be sent
    cin >> n;

    cout << "Enter Sender Address : ";
    int src_address;
    cin >> src_address;

    cout << "Enter Receiver Address : ";
    int dest_address;
    cin >> dest_address;

    while (1)
    {

        struct msg f1;
        if (resend_flag)
        {
            f1 = tempf;
        }
        else
        {
            f1.msgtype = 1;
            f1.msg_sqnum = i;
            f1.src = src_address;
            f1.dest = dest_address;
            
            for (int i = 0; i < SIZE; i++)
            {
                f1.msg_data[i] = (char)(rand() % 2 + 48);
            }
            addCRC(&f1);
            f1.msg_sqnum =i;
        }
        cout << "Sending Frame " << f1.msg_sqnum << " " ;
        cout << f1.msg_data << '\n';
    
        int p = msgsnd(msg_id, &f1, sizeof(f1), 0);
        //resend sleep
        if(resend_flag){
            sleep(3);
        }
        tempf = f1;

        int ack_flag = 0;
        int temptime = timeout;
        struct ack ackFrame;
        int timeout = 10000000;
        while (timeout--)
        {
            
            int ack_rec = msgrcv(ack_id, &ackFrame, sizeof(ackFrame), 1, 1 | IPC_NOWAIT);

            if (ack_rec >= 0 && f1.msg_sqnum == ackFrame.msg_sqnum && ackFrame.src == src_address)
            {
                cout << "Acknowledgement received\n\n";
                ack_flag = 1;
                break;
            }
        }
        if (ack_flag == 1)
        {
            i = i +  1; 
            if (i == n){
                break;
            }
            resend_flag = false;
        }
        else
        {
            cout << "Ack Timeout : ";
            cout << "Resending Message\n";
            resend_flag = true;
        }
    }
    struct msg f;
    f.msgtype = 1;
    f.msg_sqnum = -1;
    
    msgsnd(msg_id, &f, sizeof(f), 0);
}
