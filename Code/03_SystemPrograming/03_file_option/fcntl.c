#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int fd; //定义为全局变量，为了收到SIGINT时能够正确关闭文件

void pro_exit(int sig)
{
/*     利用fcntl实现文件描述符复制    */
    fcntl(STDOUT_FILENO, F_DUPFD, 4);
    write(4, "---------------A dup test\n", sizeof("---------------A dup test\n"));
    close(fd);
    exit(0);
}

int main(int argc, char **argv) {
/*     利用fcntl给设备文件或套接字文件设置阻塞属性 F_GETFL/F_SETFL */
    signal(SIGINT, pro_exit);
    fd = open("/dev/tty", O_RDONLY);
    if (fd < 0) {
        perror("open error");
        exit(-1);
    }
    int flag = fcntl(fd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
    int n = 0;
    char buf[50] = {0};
    while (n = read(fd, buf, sizeof(buf))) {
        if (n < 0) {
            if (n == EAGAIN) {  //read出错
                perror("read error");
                exit(-1);
            } else {    //read被设置了非阻塞属性
                printf("I am blocked...\n");
                sleep(1);
                continue;
            }
        }
        write(STDOUT_FILENO, buf, sizeof(buf));
        bzero(buf, sizeof(buf));
    }

    return 0;
}