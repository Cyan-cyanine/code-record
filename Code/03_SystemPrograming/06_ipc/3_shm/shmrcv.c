#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024

int main(void)
{
    int shmid = shmget(ftok(".", 1), SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shm error");
        exit(-1);
    }
    char *shm_p = shmat(shmid, NULL, 0); // 0代表以共享内存的访问权限为可读可写
    printf("%s",shm_p);
    shmdt(shm_p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}