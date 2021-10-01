#include<sys/ipc.h>
#include<sys/msg.h>
#include<bits/stdc++.h>

using namespace std;

int main(){
    key_t a, b, c;
    a = ftok("progfile1", 60);
    b = ftok("progfile2", 70);
    c = ftok("progfile3", 80);
    

    int a_id = msgget(a, 0666 | IPC_CREAT);
    int b_id = msgget(b, 0666 | IPC_CREAT);
    int c_id = msgget(c, 0666 | IPC_CREAT);

    msgctl(a_id ,IPC_RMID,NULL);
    msgctl(b_id ,IPC_RMID,NULL);
    msgctl(c_id ,IPC_RMID,NULL);
}
