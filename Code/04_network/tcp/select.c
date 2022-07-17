#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define err_handle(m) \
    do                \
    {                 \
        perror(m);    \
        exit(-1);     \
    } while (0)

void addFdtoArr(int fd, int *arr, int *maxIndex) //将fd添加到Arr数组
{
    int i;
    for (i = 0; arr[i] != -1; i++)
        ;
    arr[i] = fd;
    if (i > *maxIndex)
        *maxIndex = i;
}

void delFdFromArr(int fd, int *arr, int *maxIndex) //将fd从数组删除
{
    int i;
    for (i = 0; arr[i] != fd; i++)
        ;
    arr[i] = -1;
    if (i == *maxIndex)
        (*maxIndex)--;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("input like this:./exeFile [port]\n");
        return -1;
    }

    // 1.创建监听套接字
    int lFd = socket(AF_INET, SOCK_STREAM, 0);
    if (lFd == -1)
        err_handle("socket error");
    int on = 1;
    setsockopt(lFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    // 2.定义本地地址结构体并绑定到套接字
    struct sockaddr_in local_addr, cli_addr;
    socklen_t cli_addr_len;
    local_addr.sin_family = AF_INET;
    // local_addr.sin_port = htons(atoi(argv[1]));
    local_addr.sin_port = htons(10086);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lFd, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if (ret == -1)
        err_handle("bind error");
    listen(lFd, 128); //同时监听的最大值为128,注意这个值不是最大用户连接数量

    // 3.
    int cnFdArr[FD_SETSIZE - 3];          //存储已建立连接的套接字描述符数组，FD_SETSIZE表示最大文件描述符数量，3表示标准输入，输出，出错
    memset(cnFdArr, -1, sizeof(cnFdArr)); //初始化为-1
    int maxIndex = -1;                    //数组最大成员下标

    fd_set r_set, all_set;
    FD_ZERO(&all_set);                      //清空all_set
    FD_SET(lFd, &all_set);                  //将lFd添加到all_set
    int nRead, nReadyFd, cnFd, maxFd = lFd; // nRead为读取的字节数, nReadyFd为select返回的文件描述符数量，cnFd为与客户端建立通信的套接字,maxFd为当前活动的最大文件描述符
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    char *buf = malloc(BUFSIZ);
    if (buf == NULL)
        err_handle("malloc error");
    int z = 0;
    while (1)
    {
        r_set = all_set;
        nReadyFd = select(maxFd + 1, &r_set, NULL, NULL, &timeout);
        if (nReadyFd < 0)
            err_handle("select error");
        else if (FD_ISSET(lFd, &r_set)) //若返回的描述符里有lFd说明此时有客户端来建立连接
        {
            cli_addr_len = sizeof(cli_addr); //传入传出参数，值随时可能发生更改，因此调用accept前需要重新赋值
            cnFd = accept(lFd, (struct sockaddr *)&cli_addr, &cli_addr_len);
            if (cnFd == -1)
                err_handle("accept error");
            printf("%s [connected]\n", inet_ntoa(cli_addr.sin_addr));
            addFdtoArr(cnFd, cnFdArr, &maxIndex);
            FD_SET(cnFd, &all_set); //将已成功建立连接的套接字加入到all_set
            if (cnFd > maxFd)
                maxFd = cnFd;
            if (nReadyFd == 1)
                continue;
        }
        for (int i = 0; i <= maxIndex; i++)
        {
            if (cnFdArr[i] == -1)
                continue;
            if (FD_ISSET(cnFdArr[i], &r_set))
            {
                bzero(buf, BUFSIZ);
                nRead = read(cnFdArr[i], buf, BUFSIZ);
                if (nRead < 0)
                    err_handle("read error");
                else if (nRead == 0)
                {
                    if (cnFdArr[i] == maxFd)
                        maxFd--;
                    FD_CLR(cnFdArr[i], &all_set);
                    close(cnFdArr[i]);
                    delFdFromArr(cnFdArr[i], cnFdArr, &maxIndex);
                    printf("someone [closed]\n");
                }
                else
                {
                    write(STDOUT_FILENO, buf, BUFSIZ);
                    // printf("[from %d]:%s\n", cnFdArr[i], buf); //打印对端发送的消息
                    printf("%d\n", ++z);
                }
            }
        }
    }
    free(buf);
    return 0;
}
