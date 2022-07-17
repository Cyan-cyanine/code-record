#include "sem.h"
#include "sem.c"

int main(void) {
    signal(SIGINT, rmSource);
    shmid = shmget(ftok(".", 1), 2,IPC_CREAT|0666);
    addr = shmat(shmid, NULL, 0);
    semid =
        semget(ftok(".", 2), SEM_SIZE,
               IPC_CREAT | IPC_EXCL | 0666);  // IPC_EXCL的作用是创建失败会报错
    if (semid >= 0) {
        sem_init(semid, DATA, 0);
        sem_init(semid, SPACE, 1);
    } else {
        semid = semget(ftok(".", 2), 2, 0666);
    }
    char *info = "123456789";
    int i = 0;
    printf("semid = %d\n",semid);
    while(1)
    {
        sem_p(semid, SPACE);
        memcpy(addr, info+i, 1);
        usleep(500000); //延时0.5s
        i=(i+1)%9;
        sem_v(semid, DATA);
    }
    return 0;
}
