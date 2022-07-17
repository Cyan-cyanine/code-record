#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    int ret = pipe(fd);
    if(ret==-1)
    {
        perror("pipe error.");
        exit(1);
    }
    pid_t pid;
    pid = fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid > 0)
    {
        close(fd[1]);//关闭写端
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        perror("execlp wc error");
    }
    else if(pid==0)
    {
        close(fd[0]);//关闭读端
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        perror("execlp error");
    }
    return 0;
}
