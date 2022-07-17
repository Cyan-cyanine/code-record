#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 50
#define NUM 2


int main(int argc, char **argv)
{
    if(argc!=3)
    {
        printf("please input 2 arguments.\n");
        return -1;
    }
    char buf[SIZE*NUM];
    FILE *fp1 = fopen(argv[1],"r");
    FILE *fp2 = fopen(argv[2],"w");
    if(fp1==NULL||fp2==NULL)
    {
        printf("fopen error.");
        return -1;
    }
    long begin,end;
    while(1)
    {
        begin = ftell(fp1);
        bzero(buf,SIZE*NUM);
        if(fread(buf,SIZE,NUM,fp1)<NUM) //读取的块数少于预定块数
        {
            if(feof(fp1))   //到达了文件尾部
            {
                end = ftell(fp1);
                fwrite(buf,end-begin,1,fp2);
                printf("%s\n",buf);
                printf("complete.\n");
                break;
            }
            else if(ferror(fp1))    //遇到错误
            {
                printf("fread error.\n");
                break;
            }
        }
        fwrite(buf,SIZE,NUM,fp2);
        printf("%s\n",buf);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
