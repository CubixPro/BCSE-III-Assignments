#include "frame.hpp"
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <unistd.h>


int main() {
  key_t rec_key, ack_key;
  int rec_id, ack_id;

  rec_key = ftok("progfile3", 76);
  ack_key = ftok("progfile2", 70);

  rec_id = msgget(rec_key, 0666 | IPC_CREAT);
  ack_id = msgget(ack_key, 0666 | IPC_CREAT);

  int rn = 0;

  int numFrames;
  cin >> numFrames;

  bool nckSend = false;
  bool ackNeeded = false;

  bool marked[numFrames];

  for (int i = 0; i < numFrames; i++) {
    marked[i] = false;
  }

  vector<struct msg> finalFrames(numFrames);

  struct msg f;

  while (true) {
    int p = msgrcv(rec_id, &f, sizeof(f), 1, 0);
    if (p >= 0) {
      if (!checkCRC(&f) && !nckSend) {
        struct acknowledgement nck;
        nck.msgtype = 1;
        nck.msg_type = -1;
        nck.msg_sqnum = rn;
        cout << "Sending Negetive Acknowledgement for Frame " << rn << '\n';
        msgsnd(ack_id, &nck, sizeof(nck), 0);
        nckSend = true;
        sleep(2);
      } // corrupted frame,sends nck
      if (f.msg_sqnum != rn && !nckSend) {
        struct acknowledgement nck;
        nck.msgtype = 1;
        nck.msg_type = -1;
        nck.msg_sqnum = rn;
        cout << "Sending Negetive Acknowledgement for Frame " << rn << '\n';
        msgsnd(ack_id, &nck, sizeof(nck), 0);
        nckSend = true;
        int sN = f.msg_sqnum;
        if (sN < numFrames && !marked[sN]) {
          finalFrames[sN] = f;
          marked[sN] = true;
          while (marked[rn]) {
            cout << "Received Frame " << rn << '\n';
            cout << "Frame Data : " << f.msg_data << '\n';
            rn = rn + 1;
            ackNeeded = true;
          }
          if (ackNeeded) {
            struct acknowledgement ack;
            ack.msgtype = 1;
            ack.msg_type = 1;
            ack.msg_sqnum = rn;
            ackNeeded = false;
            nckSend = false;
          }
        }
      }
    }
  }
}