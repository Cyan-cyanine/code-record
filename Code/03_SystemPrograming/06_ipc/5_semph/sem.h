#ifndef SEM_H
#define SEM_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>

#define DATA 0
#define SPACE 1
#define SEM_SIZE 2

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

static int semid, shmid;
static char *addr;

void sem_init(int semid, int semnum, int val);
void sem_p(int semid, int semnum);
void sem_v(int semid, int semnum);
#endif
