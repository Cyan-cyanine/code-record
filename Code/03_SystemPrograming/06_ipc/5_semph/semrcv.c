#include "sem.h"
#include "sem.c"

int main(void) {
    shmid = shmget(ftok(".", 1), 2,IPC_CREAT|0666);
    addr = shmat(shmid, NULL, 0);
    semid =
        semget(ftok(".", 2), SEM_SIZE,
               IPC_CREAT | IPC_EXCL | 0666);  // IPC_EXCL的作用是创建失败会报错
    if (semid >= 0) {
        sem_init(semid, DATA, 0);
        sem_init(semid, SPACE, 1);
    } else {
        semid = semget(ftok(".", 2), SEM_SIZE, 0666);
    }
    printf("semid = %d\n",semid);
    while(1)
    {
        sem_p(semid, DATA);
        printf("%c", *addr);
        fflush(stdout);
        sem_v(semid, SPACE);
    }

    return 0;
}
