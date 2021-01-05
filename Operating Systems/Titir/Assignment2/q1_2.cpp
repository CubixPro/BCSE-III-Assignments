#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>


using namespace std;

typedef struct{
sem_t mut;
int i;
} semint;

int x = 2;
int main()
{
    semint *sem;
    size_t size = sizeof(semint);
    sem = (semint*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED , 0, 0);

    sem_init(&sem->mut, 1, 1);

    //sem_init(&mut, 1, 1);
    int cpX = fork();
    if (cpX == 0)
    {
        //child A code

        for (int i = 0; i < 10; i++)
        {
            sem_wait(&sem->mut);
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
            for (int i = 0; i < 10; i++)
            {
                cout << "Inside Y:" << getpid() << ", " << i << '\n';
                sleep(rand() % 5);
                sem_post(&sem->mut);
                sleep(1);
            }
            //sem_wait(&mut);
           exit(0); 
        }
        else
        {
            //sleep(50);
            sem_destroy(&sem->mut);
            
            wait(NULL);
            wait(NULL);
            exit(0);
            // wait(NULL);
        }
    }
}