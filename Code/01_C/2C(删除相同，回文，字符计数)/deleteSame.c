#include <stdio.h>
#include <string.h>

#define SIZE 50

int main(void)
{
    int i,j,k;
    char s[SIZE];
    printf("Input string:");
    gets(s);
    for(i=0;s[i];i++)
    {
        for(j=k=i+1;s[j];j++)
            if(s[i]!=s[j])
                s[k++]=s[j];
        s[k] = 0;
    }
    printf("%s\n",s);
    return 0;
}