#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *routine(void *arg)
{
    // pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);      //②响应取消函数(默认)
    // pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);     //①忽略取消函数

    // pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);     //②延迟响应(默认)
    // pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); //③立即响应
    for (int i = 0; i < 10000; i++)
        for (int j = 0; j < 100000; j++)
            ;

    int n = 5;
    while (n--)
        fprintf(stderr, "[%c] ", '1');
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, NULL, routine, NULL);
    pthread_cancel(tid);
    if (pthread_join(tid, NULL) == 0)
        printf("join tid successfully.\n");
    pthread_exit(NULL);
    return 0;
}