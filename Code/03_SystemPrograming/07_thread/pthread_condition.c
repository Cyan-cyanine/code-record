#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

pthread_mutex_t m;//互斥锁
pthread_cond_t v; //条件等待队列
int balance = 0;  //共享余额

void *routine(void *arg)
{
    pthread_mutex_lock(&m);
    int n = *(int *)arg + 1;
    while (balance < 100) //注意此处为什么不用if，当与其他线程争抢资源处于劣势时需要重复检查可用的剩余资源
    {
        fprintf(stderr, "t[%d] wait for money.\n", n);
        pthread_cond_wait(&v, &m);  //等待时需要解除互斥锁，所以第二个参数需要传入互斥锁地址
    }
    //取钱
    balance-=100;
    fprintf(stderr, "t[%d] take 100$.\n", n);
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&v, NULL);
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int i;
    for (i = 0; i < 5; i++)
    {
        pthread_create(&tid, NULL, routine, (void *)&i);
        usleep(5);  //防止i的内容被践踏导致不正确传值
    }
    //打钱
    pthread_mutex_lock(&m);
    printf("[save money].\n");
    balance += 5 * 100;
    pthread_cond_broadcast(&v);
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
    return 0;
}