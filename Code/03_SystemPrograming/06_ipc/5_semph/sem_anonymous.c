#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

sem_t space, data;

void *routine(void *arg)
{
    char *buf = arg;
    while (1)
    {
        sem_wait(&data);
        fprintf(stderr, "bytes = %d\ncontent:%s", strlen((char *)buf), (char *)buf);
        sem_post(&space);
    }
}

int main(void)
{
    sem_init(&data, 0, 0); //第一个0代表信号量用于线程，第二个是初始化的值
    sem_init(&space, 0, 1);
    char buf[50];
    pthread_t tid;
    pthread_create(&tid, NULL, routine, (void *)buf);
    while (1)
    {
        sem_wait(&space);
        bzero(buf, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        sem_post(&data);
    }
    return 0;
}
