#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <semaphore.h>


using namespace std;

sem_t mut;

int x = 2;
int main()
{
    int cpX = fork();
    sem_init(&mut, 1, 1);
    if (cpX == 0)
    {
        //child A code
        for (int i = 0; i < 1; i++)
        {
            cout << "Inside X:" << getpid() << ", " << i << '\n';
            sleep(rand() % 5);
        }
        
        exit(0);
    }
    else
    {
        int cpY = fork();
        if (cpY == 0)
        {
            //child B code
            for (int i = 0; i < 1; i++)
            {
                cout << "Inside Y:" << getpid() << ", " << i << '\n';
                sleep(rand() % 5);
            }
            sem_wait(&mut);
           exit(0); 
        }
        else
        {
            //sleep(50);
            
            wait(NULL);
            wait(NULL);
            exit(0);
            // wait(NULL);
        }
    }
}