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

    for (int i = 0; i < 4; i++) {
        if (mkfifo(fifos[i], 0777) == -1) {
                return 1;
            
        }
    }

    int fd[4];

    char mes[200];
    int n;
    for (int i = 0; i < 4; i++) {
        fd[i] = open(fifos[i], O_WRONLY);
        if (fd[i] == -1) {
            return 2;
        }
    }

    while (1) {
        printf("Enter message: ");
        fgets(mes, 200, stdin);
        mes[strlen(mes) - 1] = '\0';
        n = strlen(mes) + 1;
        for (int i = 0; i < 4; i++) {
            if (write(fd[i], &n, sizeof(int)) == -1) {
                return 3;
            }
            if (write(fd[i], mes, sizeof(char) * n) == -1) {
                return 4;
            }
        }

        if (strcmp(mes, "q") == 0) {
            break;
        }
        printf("Sent information.\n");
    }
    for (int i = 0; i < 4; i++)
        close(fd[i]);
    return 0;
};
