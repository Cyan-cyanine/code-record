#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>

#define err_handle(m) \
    do                \
    {                 \
        perror(m);    \
        exit(-1);     \
    } while (0)

struct info
{
    int fd;
    struct sockaddr_in addr;
};

int listenFd;

void *readSocket(void *arg)
{
    struct info cliMsg;
    char buf[BUFSIZ];
    cliMsg.addr = ((struct info *)arg)->addr;
    cliMsg.fd = ((struct info *)arg)->fd;
    int readN;
    while (1)
    {
        readN = read(cliMsg.fd, buf, sizeof(buf));
        if (readN < 0)
            err_handle("read error");
        else if (readN == 0)
        {
            if (errno == EAGAIN) // read的目标被设置了非阻塞
                continue;
            close(cliMsg.fd);
            printf("%s has [closed]\t\t×\n", inet_ntoa(cliMsg.addr.sin_addr));
            pthread_exit(NULL); //对端关闭
        }
        printf("[rcv from %s]:%s", inet_ntoa(cliMsg.addr.sin_addr), buf);
    }
}

void sys_exit(int sigNum)
{
    close(listenFd);
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("input like this:./exeFile [port number]\n");
        return -1;
    }
    signal(SIGINT, sys_exit);
    pthread_t pid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置分离属性

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0)
        err_handle("socket error");
    struct sockaddr_in srv_addr, cli_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(atoi(argv[1]));
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(listenFd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (ret != 0)
        err_handle("bind error");
    ret = listen(listenFd, 128);
    struct info tmp;
    int cnfd;
    socklen_t cli_addr_len = sizeof(cli_addr);
    while (1)
    {
        cnfd = accept(listenFd, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (cnfd == -1)
            err_handle("accept error");
        printf("%s has [connected]\t\t√\n", inet_ntoa(cli_addr.sin_addr));
        tmp.addr = cli_addr;
        tmp.fd = cnfd;
        pthread_create(&pid, &attr, readSocket, (void *)&tmp);
    }
    return 0;
}