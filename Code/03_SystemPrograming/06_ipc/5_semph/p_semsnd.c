#include "p_sem.h"

void rmSource(int arg)
{
    shmdt(shm_p);
    shmctl(shmid, IPC_RMID, NULL);
    sem_close(data);
    sem_close(space);
    sem_unlink(DATA);
    sem_unlink(SPACE);
    printf("rm source complete.\n");
    exit(0);
}

int main(void)
{
    signal(SIGINT, rmSource);
    shmid = shmget(ftok(".", 1), SHM_SIZE, IPC_CREAT | 0666);
    shm_p = shmat(shmid, NULL, 0);
    data = sem_open(DATA, O_CREAT, 0666, 0);
    space = sem_open(SPACE, O_CREAT, 0666, 1);
    char *arr = "1234567890";
    int i = 0;
    while (1)
    {
        sem_wait(space);
        memcpy(shm_p, arr + i, 1);
        usleep(500000);
        sem_post(data);
        i = (i + 1) % 10;
    }
    return 0;
}