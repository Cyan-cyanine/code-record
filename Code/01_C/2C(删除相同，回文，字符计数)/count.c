#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50

bool counting(char *string,int n)
{
    if(n==0)
    {
        printf("Invalid input，please try again:");
        return false;
    }
    int blank, num, capital, minuscule;
    blank = num = capital = minuscule = 0;
    for (int i=0;i<n;++i)
    {
        if(string[i] == 32)
            blank++;
        else if(string[i]>='a'&&string[i]<='z')
            minuscule++;
        else if(string[i]>='A'&&string[i]<='Z')
            capital++;
        else if(string[i]>='0'&&string[i]<='9')
            num++;
    }
     printf("num=%d\nblank=%d\ncaptial=%d\nminuscule=%d\n",num,blank,capital,minuscule);
    return true;                   
}

int main(void)
{
    char buf[SIZE];
    printf("Inpunt a string:");
    do{
        fgets(buf,SIZE,stdin);
    }while(!counting(buf,strlen(buf)));
    return 0;
}