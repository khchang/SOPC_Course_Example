#include    <system.h>
#include    <stdio.h>
#include    <sys/alt_alarm.h>
#include    <sys/time.h>
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
    StrLCD_Init();   
}

void Timer_Init(void)
{
    struct timeval set_time;
    
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
        alt_alarm_start(&alarm0, alt_ticks_per_second(), alarm0_callback, NULL);
    }    
}

void StrLCD_Init(void)
{
    printf("\x1B[2J");                                              // Clears the whole screen.
    printf("\x1B[1;1H");                                            // Moves the cursor to the x=1, y=1
    printf(" 0Day, 0Hour\n");
    printf(" 0Min, 0Sec\n");    
}

alt_u32 alarm0_callback(void *context)
{
    struct timeval current_time;
    int day=0, hour=0, minute=0, second=0;
    unsigned int current_sec=0;
    
    if(gettimeofday(&current_time, NULL))
    {
        printf("No system clock is available.\n");
        return 0;                                                       // Stop alarm1
    }
    else
    {
        current_sec=(unsigned int)current_time.tv_sec;
        second=(int)current_sec%60;
        current_sec/=60;
        minute=(int)current_sec%60;
        current_sec/=60;
        hour=(int)current_sec%60;
        current_sec/=24;
        day=(int)current_sec;
        printf("\x1B[2J");                                              // Clears the whole screen.
        printf("\x1B[1;1H");                                            // Moves the cursor to the x=1, y=1
        printf("% dDay, %dHour\n",day,hour);
        printf("% dMin, %dSec\n",minute,second);       
        return alt_ticks_per_second();
    }
}
