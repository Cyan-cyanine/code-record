#include "p_sem.h"

int main(void)
{
    shmid = shmget(ftok(".", 1), SHM_SIZE, IPC_CREAT | 0666);
    shm_p = shmat(shmid, NULL, 0);
    data = sem_open(DATA, O_CREAT, 0666);
    space = sem_open(SPACE, O_CREAT, 0666);
    while (1)
    {
        sem_wait(data);
        fprintf(stdout, "%c", *shm_p);
        fflush(stdout);
        sem_post(space);
    }
    return 0;
}