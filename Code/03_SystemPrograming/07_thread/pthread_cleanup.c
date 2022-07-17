#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t m;

void handler(void *arg)
{
    pthread_mutex_unlock(&m);
}

void *routine(void *arg)
{
    pthread_cleanup_push(handler, NULL); //加锁前，将handler压入线程取消处理例程的栈中，以防中途被取消
    pthread_mutex_lock(&m);
    char *info = (char *)arg;
    int n = 5;
    while (n--)
    {
        fprintf(stderr, "%s", info);
        sleep(1);
    }
    pthread_mutex_unlock(&m);
    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_mutex_init(&m, NULL);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, routine, (char *)"[t1]");
    pthread_create(&tid2, NULL, routine, (char *)"[t2]");
    sleep(1);
    pthread_cancel(tid1);
    printf("send cancel to tid1.\n");
    if ((errno = pthread_join(tid1, NULL)) == 0)
        printf("join t1 successfully.\n");
    else
        perror("fail to join t1");
    if ((errno = pthread_join(tid2, NULL)) == 0)
        printf("join t2 successfully.\n");
    else
        perror("fail to join t2");
    return 0;
}