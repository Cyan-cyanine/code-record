#include <stdio.h>
#include <stdbool.h>
#define size 20

int scpm(char *a,char *b)
{
    for(int i=0;a[i]!=0 || b[i]!=0;i++)
    {
        if(a[i]==b[i])
            continue;
        else
            return a[i]-b[i];
    }
}

int main()
{
    char a[size],b[size];
    printf("请输入第一个字符串:");
    scanf("%s",a);
    getchar();
    printf("请输入第二个字符串:");
    scanf("%s",b);
    getchar();
    printf("%d\n",scpm(a,b));
    return 0;
}