#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <thread>
#include "buffer.hpp"

using namespace std;

typedef struct{
    sem_t mut;
    int i;
}semint;

class Producer{

};

//does create issues

class Consumer{

};


int main(){
    semint *mutexval;
    semint *empty;
    semint *full;

    mutexval = (semint *)malloc(sizeof(semint));
    empty = (semint *)malloc(sizeof(semint));
    full = (semint *)malloc(sizeof(semint));
    int buffersize;
    cout << "Enter the buffer size : ";
    cin >> buffersize;

    buffer produced[buffersize];

    sem_init(&mutexval->mut, 0, 1);
    sem_init(&empty->mut, 0, 0);
    sem_init(&full->mut, 0, buffersize);

    int producers;
    int consumers;

    cout << "Enter the number of producers : ";
    cin >> producers;
    cout << "Enter the number of consumers : ";
    cin >> consumers;
    int i = 0;

    auto producerFunc = [&](int a){
        while(true){
            if(i == buffersize){
                continue;
            }
        buffer newprod;
        newprod.producer_id = a;
        newprod.payload = rand()%10000;

        produced[i] = newprod;
        i++;

        sem_wait(&mutexval->mut);
        cout << "Producer : " << newprod.producer_id << ' ' << newprod.payload << " " << "\n" ;
        sem_post(&mutexval->mut);
 
        sleep(3);
        }

    };

    auto consumerFunc = [&](int a){
        while(true){
            if(i == 0){
                continue;
            }

            buffer newprod;  
            i--;
            newprod = produced[i];
            sem_wait(&mutexval->mut);
            cout << "Consumer : " << newprod.producer_id << ' ' << newprod.payload << " " << a << "\n" ;
            sem_post(&mutexval->mut);

            sleep(3);
        }
    };

    vector<thread> threads;

    for(int i = 0 ; i < producers ; i++){
        thread t(producerFunc, i);
        threads.push_back(move(t));
    }

    for(int j = 0 ; j < consumers ; j++){
        thread t(consumerFunc, j);
        threads.push_back(move(t));
    }

    for(auto &t : threads){
        t.join();
    }


}