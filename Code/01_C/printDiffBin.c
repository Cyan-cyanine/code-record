#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int main( int argc, char** argv ) {
    unsigned int A,B;
    int count = 0;
    scanf("%x %x", &A, &B);
    while( A!=0 || B!=0)
    {
        if((A&1) != (B&1))
        {
            count++;
        }
        A = A>>1;
        B = B>>1;
    }
    printf("%d\n",count);
    return 0;
}