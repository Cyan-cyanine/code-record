#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void *routine1(void *arg)
{
    char *ret = "routine1.\n";
    pthread_exit((void *)ret); //此处的返回值就是函数的返回值
}

void *routine2(void *arg)
{
    // pthread_detach(pthread_self());//pthread_self()获取本线程tid
    char *ret = "routine2.\n";
    pthread_exit((void *)ret); //此处的返回值就是函数的返回值
}

int main(void)
{
    pthread_attr_t attr1, attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED); //给attr2添加分离属性
    pthread_t tid1, tid2;
    pthread_create(&tid1, &attr1, routine1, "This is the first thread.\n");
    pthread_create(&tid2, &attr2, routine2, "This is the second thread.\n");

    printf("This is main thread.\n");
    void *ret1, *ret2;
    if ((errno = pthread_join(tid1, &ret1)) == 0)
    {
        fprintf(stderr, "%s", (char *)ret1);
    }
    else
    {
        perror("fail to join the thread1");
    }
    // sleep(1);
    if ((errno = pthread_join(tid2, &ret2)) == 0)
    {
        fprintf(stderr, "%s", (char *)ret2);
    }
    else
    {
        perror("fail to join the thread2");
    }
    pthread_exit(NULL);
    return 0;
}
