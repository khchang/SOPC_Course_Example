#include    <system.h>
#include    <stdio.h>
#include    <unistd.h>
#include    <sys/alt_timestamp.h>
#include    <altera_avalon_pio_regs.h>
#include    "main.h"

int main(void)
{
    unsigned int timer_count=0;
    unsigned int current_sec=0;
    alt_u32 timestamp_count=0;
    
    SYS_Init();
    
    while(1)
    {
        timestamp_count=alt_timestamp();
        current_sec=timer_count;        
        printf("Seconds: %u, Interval time(timestamp): %f\n", current_sec, timestamp_count*1/Timer_Clock);
        IOWR(SEG7_BASE,0,SEG7_Table[(current_sec%60)%10]);               // Second
        IOWR(SEG7_BASE,1,SEG7_Table[(current_sec%60)/10]);
        current_sec/=60;
        IOWR(SEG7_BASE,2,SEG7_Table[(current_sec%60)%10]);               // Minute
        IOWR(SEG7_BASE,3,SEG7_Table[(current_sec%60)/10]);
        current_sec/=60;
        IOWR(SEG7_BASE,4,SEG7_Table[(current_sec%60)%10]);               // Hour
        IOWR(SEG7_BASE,5,SEG7_Table[(current_sec%60)/10]);
        current_sec/=24;
        IOWR(SEG7_BASE,6,SEG7_Table[(current_sec%24)%10]);               // Day
        IOWR(SEG7_BASE,7,SEG7_Table[(current_sec%24)/10]);
        timer_count++;
        if(alt_timestamp_start())
        {
            printf("The timestamp is not available.\n");
            return 1;
        }        
        usleep(1*1000*1000);                                            // Count * us
    }
    return 0;
}

void SYS_Init(void)
{
    SEG7_Clear();
}

void SEG7_Clear(void)
{
    unsigned char i=0;
    for(i=0;i<SEGNUM;i++)
    {
        IOWR(SEG7_BASE,i,0);
    }
}
