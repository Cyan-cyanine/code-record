#include <stdio.h>

int main(void)
{
    int A,B;
    printf("请输入两个非零整数:");
    fscanf(stdin,"%d %d",&A,&B);
    while(A==0||B==0)
    {
        printf("输入参数错误，请重试：");
        fscanf(stdin,"%d %d",&A,&B);
    }
    if(A%2==1&&B%2==0)//A是奇数，B是偶数
        printf("%d\n",A*B);
    else if(A%2==0&&B%2==1)//A是偶数，B是奇数
        printf("%d\n",A/B);
    else if(A%2==1&&B%2==1)//A，B是奇数
        printf("%d\n",A-B);
    return 0;
}