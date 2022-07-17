#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>   //mkfifo


int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("input like this:./a.out fifo_file.\n");
        exit(-1);
    }
    if(access(argv[1],F_OK)){
        if(-1 == mkfifo(argv[1],0644)){
            perror("fifo");
            exit(-1);
        }
    }
    int fd = open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        exit(-1);
    }
    int i=0,len;
    char buf[4096];
    while(1)
    {
        len = read(fd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
        sleep(1);
    }
    return 0;
}