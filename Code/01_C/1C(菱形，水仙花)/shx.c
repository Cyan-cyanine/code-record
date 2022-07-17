#include <stdio.h>

int main(void)
{
    int n;
    int x=1,y=1,z=1;
    printf("请输入一个三位整数：");
    scanf("%d", &n);
    while (n < 100 && n > -100)
    {
        printf("输入错误，请重新输入：");
        scanf("%d", &x);
    }
    for(int i=0;i<3;i++)
    {
        x*=n/100;
        y*=n/10%10;
        z*=n%10;
    }
    if(x+y+z==n)
        printf("是水仙花数！\n");
    else
        printf("不是水仙花数！\n");
    return 0;
}