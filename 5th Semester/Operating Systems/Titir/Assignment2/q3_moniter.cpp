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
#include <mutex>

using namespace std;

mutex mtx;

typedef struct{
    sem_t mut;
    int i;
}semint;

class Producer{

};


class Consumer{

};


int main(){
    
    int buffersize;
    cout << "Enter the buffer size : ";
    cin >> buffersize;

    buffer produced[buffersize];

    

    int producers;
    int consumers;

    cout << "Enter the number of producers : ";
    cin >> producers;
    cout << "Enter the number of consumers : ";
    cin >> consumers;
    int i = 0;

    auto producerFunc = [&](int a){
        while(true){
        
        mtx.lock();
        if(i == buffersize){
            mtx.unlock();
            continue;
        }

        buffer newprod;
        newprod.producer_id = a;
        newprod.payload = rand()%10000;

        produced[i] = newprod;
        i++;

        cout << "Producer : " << newprod.producer_id << ' ' << newprod.payload << " " << "\n" ;
        mtx.unlock();
 
       
        sleep(3);
        }

    };

    auto consumerFunc = [&](int a){
        while(true){
            
            mtx.lock();
            buffer newprod;  
            if(i == 0){
                mtx.unlock();
                continue;
            }
            i--;
            newprod = produced[i];
            cout << "Consumer : " << newprod.producer_id << ' ' << newprod.payload << " " << a << "\n" ;
            mtx.unlock();
            
            //sleep(3);
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