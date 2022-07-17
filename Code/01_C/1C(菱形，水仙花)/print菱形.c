#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n;
    printf("请输入菱形的高度(奇数)：");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<abs(i-n/2);j++)
            printf("  ");
           
        for(j=0;j<n-2*abs(i-n/2);j++)
        {
            // if(j==0||j==n-2*abs(i-n/2)-1)
                printf("* ");
            // else
            //     printf("  ");
        }
        putchar(10);
    }
    return 0;
}