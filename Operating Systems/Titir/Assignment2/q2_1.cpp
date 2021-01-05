#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define MSGSIZE 100 


typedef struct
{
    char msgtext[MSGSIZE];
} msgbuf;

int main()
{
    int pid, pip[2];
    pipe(pip);
    pid = fork();

    if (pid == 0)
    {
        //caller
        msgbuf msg;
        std::cout << "Type a message to send and 'end' to stop\n";
        while(true){
            std::string str;
            std::getline(std::cin, str);
            strcpy(msg.msgtext, str.c_str()) ;           
            write(pip[1], &msg, sizeof(msgbuf));
            if(str.compare("end") == 0){
                break;
            }

        } 
        close(pip[1]);
        exit(0);
    }
    else
    {
        //receiver
        msgbuf msg;
        int nbytes;
        while ((nbytes = read(pip[0], &msg, sizeof(msgbuf))) > 0)
        {
            if(strcmp(msg.msgtext, "end") == 0){
                break;;
            }
            std::cout << "Receiver: " << msg.msgtext << '\n';
            sleep(2);

        }
        //std::cout << "here!\n";
        wait(NULL);
        exit(0);
    }
}