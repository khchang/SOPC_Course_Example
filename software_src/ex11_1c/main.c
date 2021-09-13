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

void Key_Interrupt_Routine(void* context)
{
    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Cast context to edge_capture's type. It is important that this
    be declared volatile to avoid unwanted compiler optimization. */
    
    //int day=0, hour=0, minute=0, second=0, micro_sec=0, current_sec=0;
    
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);      // Read KEY_BASE's edgecapture register.
    switch(*edge_capture_ptr)
    {
        case 0x08:  //KEY3
            if ((status&StopWatch_Stop)==StopWatch_Stop)
            {   // The stop watch is stop now.
                if(settimeofday(&stopwatch_timer,NULL))
                {
                    printf("No system clock is available.\n");
                }
                else
                {
                    //printf("It is success to set system clock.\n");
                    alt_alarm_stop(&alarm0);
                    alt_alarm_start(&alarm0, alt_ticks_per_second()/10, alarm0_callback, NULL);
                }
                status = StopWatch_Running;
            }
            else
            {
                if ((status&StopWatch_Running)==StopWatch_Running)
                {   // The stop watch is running now.
                    alt_alarm_stop(&alarm0);                                // Stop alarm1;
                    if(gettimeofday(&stopwatch_timer, NULL))
                    {
                        printf("No system clock is available.\n");
                    }
                    else
                    {
                        Display_Stop_Watch_Time();
                    }
                    status = StopWatch_Stop;
                }
            }
        break;
        case 0x04:  //KEY2
            if ((status&StopWatch_Stop)==StopWatch_Stop)
            {   // The stop watch is stop now.
                stopwatch_timer.tv_sec=0;           // Reset stop watch
                stopwatch_timer.tv_usec=0;          // Reset stop watch
                Display_Stop_Watch_Time();
            }
        break;
        case 0x02:  //KEY1   
        break;            
    }   
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, 0);                       // Reset KEY_BASE edgecapture register.

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);
    /*
	Read the PIO to delay ISR exit. This is done to prevent a
    spurious interrupt in systems with high processor -> pio
    latency and fast interrupts.
    */
}

void SYS_Init(void)
{
    Timer_Init();
    StrLCD_Init();
    status=StopWatch_Stop;
    Key_Interrupt_Init();
}

void Timer_Init(void)
{
    stopwatch_timer.tv_sec=0;           // Reset stop watch
    stopwatch_timer.tv_usec=0;          // Reset stop watch
}

void StrLCD_Init(void)
{
    printf("\x1B[2J");                                                  // Clears the whole screen.
    printf("\x1B[1;1H");                                                // Moves the cursor to the x=1, y=1
    printf("0Day 0Hour\n");
    printf("0:0:0\n");

}

void Key_Interrupt_Init(void)
{
	void* edge_capture_ptr = (void*) &edge_capture_Key;					// Read the address of the edge_capture_Key.

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY_BASE,0x0c);                     // Enables interrupts for the corresponding PIO(KEY3,KEY2) input port.
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE,0x00);                     // Reset the edge capture register.
    alt_ic_isr_register(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ, Key_Interrupt_Routine, edge_capture_ptr, 0x0);		// Register a ISR.
    Key_Interrupt_Enable();                                             // Enable ISR.
}

void Key_Interrupt_Enable(void)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, 0);                       // Reset KEY_BASE edgecapture register.
    alt_ic_irq_enable(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ);		// Enable KEY_IRQ interrupt function.
}

void Key_Interrupt_Disable(void)
{
	alt_ic_irq_disable(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ);		// Disable KEY_IRQ interrupt function.
}

alt_u32 alarm0_callback(void *context)
{
    struct timeval current_time;
    int day=0, hour=0, minute=0, second=0, micro_sec=0, current_sec=0;
    //unsigned int current_sec=0;
    
    if(gettimeofday(&current_time, NULL))
    {
        printf("No system clock is available.\n");
        return 0;                                                       // Stop alarm1
    }
    else
    {
        current_sec=(int)current_time.tv_sec;
        micro_sec=(int)current_time.tv_usec/1000;
        second=(int)current_sec%60;
        current_sec/=60;
        minute=(int)current_sec%60;
        current_sec/=60;
        hour=(int)current_sec%60;
        current_sec/=24;
        day=(int)current_sec;
        printf("\x1B[2J");                                              // Clears the whole screen.
        printf("\x1B[1;1H");                                            // Moves the cursor to the x=1, y=1
        printf("%dDay %dHour\n",day,hour);
        printf("%d:%d:%d\n",minute,second,micro_sec/100);     
        return alt_ticks_per_second()/10;
    }
}

void Display_Stop_Watch_Time(void)
{
    int day=0, hour=0, minute=0, second=0, micro_sec=0, current_sec=0;
    
    current_sec=(int)stopwatch_timer.tv_sec;
    micro_sec=(int)stopwatch_timer.tv_usec/1000;
    second=(int)current_sec%60;
    current_sec/=60;
    minute=(int)current_sec%60;
    current_sec/=60;
    hour=(int)current_sec%60;
    current_sec/=24;
    day=(int)current_sec;
    printf("\x1B[2J");                                              // Clears the whole screen.
    printf("\x1B[1;1H");                                            // Moves the cursor to the x=1, y=1
    printf("%dDay %dHour\n",day,hour);
    printf("%d:%d:%d\n",minute,second,micro_sec/100);
}
