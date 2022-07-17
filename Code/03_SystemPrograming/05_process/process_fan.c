#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int i, n;
    printf("请输入创建进程数:");
    scanf("%d", &n);
    getchar();
    for(i=0;i<n;i++)
    {
        if(fork()==0)
            break;
    }
    if(i==n)    //父进程
    {
        usleep(500);
        printf("father.\n");
        // ...
    }
    else    //子进程
    {
        printf("child.\n");
        // ...
    }
    return 0;
}