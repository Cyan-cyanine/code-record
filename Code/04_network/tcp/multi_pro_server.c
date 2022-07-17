#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define err_handle(m) \
    do                \
    {                 \
        perror(m);    \
        exit(-1);     \
    } while (0)

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("input like this:./exeFile [port number]\n");
        return -1;
    }
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd == -1)
        err_handle("socket error");
    struct sockaddr_in srv_addr, cli_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(atoi(argv[1]));
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(listenFd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (ret == -1)
        err_handle("bind error");
    listen(listenFd, 128);
    int cnfd;
    pid_t pid;
    socklen_t cli_addr_len = sizeof(cli_addr);
    while (1)
    {
        cnfd = accept(listenFd, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (cnfd == -1)
            err_handle("accept error");
        printf("cnfd = %d [connceted]\n", cnfd);
        pid = fork();
        if (pid == 0) //子进程
        {
            close(listenFd);
            int lenN;
            char *buf = malloc(BUFSIZ);
            if (buf == NULL)
                err_handle("malloc error");
            while (1)
            {
                lenN = read(cnfd, buf, BUFSIZ);
                if (lenN == 0)
                {
                    if (errno == EAGAIN)
                        continue;
                    else
                    {
                        printf("%s [closed]\n", inet_ntoa(cli_addr.sin_addr));
                        free(buf);
                        exit(0);
                    }
                }
                else if (lenN < 0)
                    err_handle("read error");
                printf("[rcv from %s]:%s\n", inet_ntoa(cli_addr.sin_addr), buf);
            }
        }
        else if (pid > 0) //父进程
        {
            pause();
        }
        else
            err_handle("fork error");
    }
    return 0;
}