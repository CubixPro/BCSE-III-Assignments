#include "frame.hpp"
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <unistd.h>

#define MAX_DELAY 5

int main() {
  srand(time(0));
  key_t rec_q, send_q;
  int rec_id, send_id;

  rec_q = ftok("progfile1", 60);
  send_q = ftok("progfile3", 80);

  rec_id = msgget(rec_q, 0666 | IPC_CREAT);
  send_id = msgget(send_q, 0666 | IPC_CREAT);
  Frame f;
  struct msg f1;
  while (1) {
    int p = msgrcv(rec_id, &f1, sizeof(f1), 1, 0);
    if (p > 0) {
      cout << "Received : ";
      cout << f1.msg_data << '\n';
      int random_number = rand() % MAX_DELAY;
      sleep(random_number);
      if (rand()%3 == 0) {
        f1.msg_data[rand() % SIZE] = '1';
      }
      msgsnd(send_id, &f1, sizeof(f1), 0);
      cout << "Sent     : " << f1.msg_data << '\n';
    }
  }
}
  // add errors