#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
    char* fifos[4] = {"fifo_1", "fifo_2", "fifo_3", "fifo_4"};

    int rcv_id = 1;
    int pid1 = fork();
    if (pid1 == -1) {
        perror("Error\n");
        return 1;
    }
    if (pid1 == 0) {
        rcv_id = 2;
        int pid2 = fork();
        if (pid2 == -1) {
            perror("Error\n");
            return 2;
        }
        if (pid2 == 0) {
            rcv_id = 4;
        }
    } else {
        rcv_id = 1;
        int pid3 = fork();
        if (pid3 == -1) {
            perror("Error\n");
            return 3;
        }
        if (pid3 == 0) {
            rcv_id = 3;
        }
    }

    int fd = open(fifos[rcv_id - 1], O_RDONLY);
    if (fd == -1) {
        return 2;
    }

    char mes[200];
    int n;

    while (1) {
        if (read(fd, &n, sizeof(int)) == -1) {
            return 3;
        }
        if (read(fd, mes, sizeof(char) * n) == -1) {
            return 4;
        }
        if (strcmp(mes, "q") == 0) {
            break;
        }
        printf("Listener %d received: %s\n", rcv_id, mes);
    }

    wait(NULL);
    wait(NULL);
    close(fd);

    return 0;
};
