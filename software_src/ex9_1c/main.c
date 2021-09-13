#include    <system.h>
#include    <stdio.h>
#include    <sys/alt_alarm.h>
#include    <sys/time.h>
#include    <sys/alt_timestamp.h>
#include    <sys/alt_irq.h>
#include    <altera_avalon_pio_regs.h>
#include    "main.h"

int main(void)
{
    SYS_Init();
    while(1)
    {
    }
    return 0;
}

void SYS_Init(void)
{
    Timer_Init();
    SEG7_Clear();   
}

void Timer_Init(void)
{
    struct timeval set_time;
    alt_u32 ticks_per_second = 0;
    
    set_time.tv_sec=0;
    set_time.tv_usec=0;
    if(settimeofday(&set_time,NULL))
    {
        printf("No system clock is available.\n");
    }
    else
    {
        printf("It is success to set system clock.\n");
        alt_alarm_stop(&alarm0);
        ticks_per_second = alt_ticks_per_second();
        alt_alarm_start(&alarm0, ticks_per_second, alarm0_callback, NULL);
    }    
}

void SEG7_Clear(void)
{
    unsigned char i=0;
    for(i=0;i<SEGNUM;i++)
    {
        IOWR(SEG7_BASE,i,0);
    }
}

alt_u32 alarm0_callback(void *context)
{
    struct timeval current_time;
    unsigned int current_sec=0;
    //unsigned int timestamp_count=0;
    alt_u32 timestamp_count=0;
    
    if(gettimeofday(&current_time, NULL))
    {
        printf("No system clock is available.\n");
        return 0;                                                       // Stop alarm0
    }
    else
    {
        timestamp_count=alt_timestamp();
        current_sec=(unsigned int)current_time.tv_sec;
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
        if(alt_timestamp_start())
        {
            printf("The timestamp is not available.\n");
        }                              
        return alt_ticks_per_second();
    }
}
