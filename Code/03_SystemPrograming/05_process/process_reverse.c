#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void fun(int i) {
    if(i==10)
        return ;
    int pid = fork();
    if(pid > 0){    //parent
        wait(NULL);
        printf("%d\t pid:%d\n",i,getpid());
        exit(0);
    }
    else if(pid == 0){  //child
        fun(++i);
        return ;
    }
}

int main(int argc, char **argv) {
    fun(0);
    return 0;
}