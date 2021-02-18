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
#include <semaphore.h>

int main() {
    sem_t *sem;
    pid_t pid1, pid2;
    srand(time(NULL));

    sem = sem_open("semaphore", O_CREAT | O_EXCL, 0777, 1);
    if (sem == SEM_FAILED) {
        perror("Could not create semaphore.\n");
        return 1;
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("Error.\n");
        return 2;
    }

    if (pid1 == 0) {
        printf("Child process X created.\n");
        for (int i = 0; i < 10; i++) {
            sem_wait(sem);
            printf("ID: %d\t Iteration number: %d\n", getpid(), i + 1);
            sleep(rand() % 4);
        }
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("Error.\n");
            return 3;
        }

        if (pid2 == 0) {
            printf("Child process Y created\n");
            for (int i = 0; i < 10; i++) {
                printf("ID: %d\t Iteration number: %d\n", getpid(), i + 1);
                sem_post(sem);
                sleep(rand() % 7);
            }
        }
    }

    wait(NULL);
    wait(NULL);

    sem_close(sem);
    sem_unlink("semaphore");

    return 0;
};
