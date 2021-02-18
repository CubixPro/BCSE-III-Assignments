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
    if (mkfifo("fifofile1", 0777) == -1) {
            perror("Could not create fifo file\n");
            return 1;
    }

    int fd = open("fifofile1", O_WRONLY);

    char* msg;
    int n;

    while (1) {
        printf("Enter message: ");
        fgets(msg, 200, stdin);
        msg[strlen(msg) - 1] = '\0';
        n = strlen(msg) + 1;

        if (write(fd, &n, sizeof(int)) == -1) {
            return 3;
        }
        if (write(fd, msg, sizeof(char) * n) == -1) {
            return 4;
        }
        if (strcmp(msg, "q") == 0) {
            break;
        }
        printf("Sent message\n");
    }

    close(fd);

    return 0;
};
