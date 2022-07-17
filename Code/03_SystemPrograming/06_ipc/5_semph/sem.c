#include "sem.h"

void sem_init(int semid, int semnum, int val)
{
    union semun arg;
    arg.val = val;
    semctl(semid, semnum, SETVAL, arg);
}

void sem_p(int semid, int semnum)
{
    struct sembuf arg[1];
    arg[0].sem_num = semnum;
    arg[0].sem_op = -1;
    arg[0].sem_flg = 0;
    semop(semid, arg, 1);
}

void sem_v(int semid, int semnum)
{
    struct sembuf arg[1];
    arg[0].sem_num = semnum;
    arg[0].sem_op = 1;
    arg[0].sem_flg = 0;
    semop(semid, arg, 1);
}

void rmSource(int arg)
{
    semctl(semid, 0, IPC_RMID);
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    printf("rm complete.\n");
    exit(0);
}