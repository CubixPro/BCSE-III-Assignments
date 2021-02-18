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
    int fd = open("fifofile1", O_RDONLY);

    char* msg;
    int n;

    while (1) {
        if (read(fd, &n, sizeof(int)) == -1) {
            return 3;
        }
        if (read(fd, msg, sizeof(char) * n) == -1) {
            return 4;
        }
        if (strcmp(msg, "q") == 0) break;
        printf("Received message: %s\n", msg);
    }

    close(fd);

    return 0;
};
