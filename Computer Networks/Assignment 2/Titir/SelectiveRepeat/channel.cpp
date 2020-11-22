#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include "frame.hpp"
#include <thread>
#include<unistd.h>

#define MAX_DELAY 5

int main(){
    key_t rec_q, send_q;
    int rec_id, send_id;
    
    rec_q = ftok("progfile1", 65);
    send_q = ftok("progfile3", 76);

    rec_id = msgget(rec_q, 0666 | IPC_CREAT);
    send_id = msgget(send_q, 0666 | IPC_CREAT);
    Frame f;
    struct msg f1;
    while(1){
        int p = msgrcv(rec_id, &f1, sizeof(f1), 1, 0);
        if(p > 0) 
            cout << f1.msg_data << '\n';
            cout << "Received\n" ; 
        int random_number = rand()%MAX_DELAY;
        sleep(random_number);
        if(rand()%5 == 1){
            f1.msg_data[rand()%SIZE] = '1';
        }
        msgsnd(send_id, &f1, sizeof(f1), 0);
        cout << "Sent\n";
    }


}

//add errors