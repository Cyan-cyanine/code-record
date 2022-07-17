#include <stdio.h>
#include <string.h>
#define SIZE 50

int main(void)
{
    char s[SIZE]={0};
    printf("Input string:");
    // fgets(s,SIZE,stdin);
    fscanf(stdin,"%s",s);
    printf("%ld\n",strlen(s));
    for(int i=0;s[i]==s[strlen(s)-1-i];i++)
        if(i==strlen(s)/2){
            printf("是回文字符!\n");
            return 0;
        }
    printf("不是回文字符!\n");
    return 0;
}