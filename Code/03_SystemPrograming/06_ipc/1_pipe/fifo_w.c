#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
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
    int fd = open(argv[1],O_WRONLY);
    if(fd==-1){
        perror("open");
        exit(-1);
    }
    int i=0;
    char buf[4096];
    while(1)
    {
        sprintf(buf,"%d is coming...\n",i++);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    

    return 0;
}