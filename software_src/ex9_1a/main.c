#include    "system.h"
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
    struct timeval current_time;
    unsigned int current_sec=0, day=0, hour=0, minute=0, second=0;
    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Cast context to edge_capture's type. It is important that this
    be declared volatile to avoid unwanted compiler optimization. */
    
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);      // Read KEY_BASE's edgecapture register.
    switch(*edge_capture_ptr)
    {
        case 0x08:  //KEY3
        break;
        case 0x04:  //KEY2
        break;
        case 0x02:  //KEY1   
            if(gettimeofday(&current_time, NULL))
            {
                printf("No system clock is available.\n");
            }
            else
            {
                current_sec=(unsigned int)current_time.tv_sec;
                printf("Seconds: %d\n", current_sec);
                second=current_sec%60;
                current_sec/=60;
                minute=current_sec%60;
                current_sec/=60;
                hour=current_sec%24;
                current_sec/=24;
                day=current_sec;
                printf("The current time is %d day %d hour %d minute %d second.\n",day,hour,minute,second);      
            }
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
    Key_Interrupt_Init();
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
    }
}

void Key_Interrupt_Init(void)
{
	void* edge_capture_ptr = (void*) &edge_capture_Key;					// Read the address of the edge_capture_Key.

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY_BASE,0x02);                     // Enables interrupts for the corresponding PIO(KEY3,KEY2,KEY1) input port.
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE,0x00);                     // Reset the edge capture register.
    alt_ic_isr_register(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ, Key_Interrupt_Routine, edge_capture_ptr, 0x0);		// Register a ISR.
    Key_Interrupt_Enable();                                             // Enable ISR.
}

void Key_Interrupt_Enable(void)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, 0);                       // Reset KEY_BASE edge capture register.
    alt_ic_irq_enable(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ);		// Enable KEY_IRQ interrupt function.
}

void Key_Interrupt_Disable(void)
{
	alt_ic_irq_disable(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ);		// Disable KEY_IRQ interrupt function.
}
