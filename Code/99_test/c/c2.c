#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int a  = 3, b=4;
    a = (a+b)-(b=a);
    printf("a=%d,b=%d\n",a,b);
    return 0;
}