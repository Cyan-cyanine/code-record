#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;  //定义互斥锁变量

void *routine(void *arg)
{
    pthread_mutex_lock(&m); //上锁
    int i=5;
    while(i--)
    {
        fprintf(stderr, "[%s] ", (char *)arg);
        usleep(500000);
    }
    putchar(10);
    pthread_mutex_unlock(&m); //解锁
    pthread_exit(NULL);
}

int main(void)
{
    pthread_mutex_init(&m, NULL);   //互斥锁初始化
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, routine, "1");
    pthread_create(&tid2, NULL, routine, "2");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_exit(NULL);
    return 0;
}