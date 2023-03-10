#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int shmid;

void sig_handler(int signum) {
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}

int main() {
    signal(SIGINT, sig_handler);
    key_t key = ftok("shmfile",65);
    shmid = shmget(key, 1024, 0666|IPC_CREAT);
    int* num = (int*) shmat(shmid, (void*)0, 0);
    while(1) {
        if (*num != 0) {
            printf("Получили: %d\n", *num);
            *num = 0;
        }
    }
    shmdt(num);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}