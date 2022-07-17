#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2], i;
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error.");
        exit(1);
    }
    pid_t pid;
    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            break;
        }
    }
    if (2 == i) {
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
    }else if (0 == i) {
        close(fd[1]);  //关闭写端
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc error");
    } else if (1 == i) {
        close(fd[0]);  //关闭读端
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        perror("execlp error");
    }
    return 0;
}
