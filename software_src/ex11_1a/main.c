#include    <system.h>
#include    <stdio.h>
#include    <unistd.h>

int main(void)
{
    int i=0;
    
    while(1)
    {
        printf("Hello World! %d\n\r",i);
        if(i<99)
        {
            i++;
        }
        else
        {
            i=0;
        }
        usleep(1*500*1000);
    }
    return 0;
}
