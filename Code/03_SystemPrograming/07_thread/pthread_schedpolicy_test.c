#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

void *routine(void *arg)
{
    // int i = 5;
    while (1)
    {
        fprintf(stderr, "%c", *(char *)arg);
        // usleep(500000);
    }
    // putchar(10);
    // pthread_exit(arg);
}

int main(void)
{
    // define the attribute
    pthread_attr_t attr1;
    pthread_attr_t attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // set detach attribute
    //  pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);
    //  pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);

    // set inherit schedual
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // set schedual policy
    pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);

    // set schedual parameter
    struct sched_param p1;
    struct sched_param p2;
    p1.sched_priority = 0; //(0~99)
    p2.sched_priority = 2; //(0~99)
    pthread_attr_setschedparam(&attr1, &p1);
    pthread_attr_setschedparam(&attr2, &p2);

    pthread_t tid1, tid2;
    pthread_create(&tid1, &attr1, routine, "1");
    pthread_create(&tid2, &attr2, routine, "2");
    pause();
    // join the thread
    //  void *ret1, *ret2;
    //  if ((errno = pthread_join(tid1, &ret1)) == 0)
    //  {
    //      printf("join tid1 success.\nThe ret is %s\n", (char *)ret1);
    //  }
    //  else{
    //      perror("fail to join tid1");
    //  }
    //  if ((errno = pthread_join(tid2, &ret2)) == 0)
    //  {
    //      printf("join tid2 success.\nThe ret is %s\n", (char *)ret2);
    //  }
    //  else{
    //      perror("fail to join tid2");
    //  }
    // main thread exit
    //  pthread_exit(NULL);
    return 0;
}