#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <Linux/input.h>

int getCoordinate()
{
    int x,y;
    int ts = open("/dev/event0",O_RDONLY);
    if(ts==-1)
    {
        printf("open event0 error.\n");
        return -1;
    }
    struct input_event buf;
    bzero(&buf,sizeof(buf));
    read(ts,&buf,sizeof(buf));
    if(buf.type == EV_ABS)
    {
        if(buf.code == ABS_X)
        {
            x = buf.value;
        }
        if(buf.code == ABS_Y)
        {
            y = buf.value;
        }
    }
}

int main(void)
{

    return 0;
}