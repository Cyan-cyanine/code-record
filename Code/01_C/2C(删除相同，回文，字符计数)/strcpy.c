#include <stdio.h>
#include <string.h>
#define SIZE 50

char *myStrCpy(char *dest, char*src, int n)
{
    for(int i=0;i<n;i++)
        dest[i] = src[i];
    return dest;
}

int main(void)
{
    char dest[SIZE];
    char src[SIZE];
    fgets(src,SIZE,stdin);
    printf("%s",myStrCpy(dest,src,SIZE));
    return 0;
}