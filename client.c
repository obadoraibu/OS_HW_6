#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int shmid;

void sig_handler(int signum) {
    shmdt(shmat(shmid, (void*)0, 0));
    exit(0);
}

int main() {
    signal(SIGINT, sig_handler);
    key_t key = ftok("shmfile",65);
    shmid = shmget(key, 1024, 0666|IPC_CREAT);
    int* num = (int*) shmat(shmid, (void*)0, 0);
    srand(time(0));
    while(1) {
        int rand_num = rand() % 10 + 1;
        *num = rand_num;
        printf("Отправили: %d\n", rand_num);
        sleep(1);
    }
    shmdt(num);
    return 0;
}