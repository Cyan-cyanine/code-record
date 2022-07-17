#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;    //定义读写锁

void *routine(void *arg)
{
    // pthread_rwlock_wrlock(&rwlock); //写锁
    pthread_rwlock_rdlock(&rwlock); //读锁
    int i=5;
    while(i--)
    {
        fprintf(stderr, "[%s] ", (char *)arg);
        usleep(500000);
    }
    putchar(10);
    pthread_rwlock_unlock(&rwlock); //解锁
    pthread_exit(NULL);
}

int main(void)
{
    pthread_rwlock_init(&rwlock, NULL); //读写锁初始化
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, routine, "1");
    pthread_create(&tid2, NULL, routine, "2");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_exit(NULL);
    return 0;
}