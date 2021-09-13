/*
 * main.c
 *
 *      Author: kh
 */
#include    "system.h"
#include    <altera_avalon_pio_regs.h>
#include	<alt_types.h>
#include    <sys/alt_irq.h>
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

    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);      // Read KEY_BASE's edge capture register.
    switch(*edge_capture_ptr)
    {
        case 0x08:
            IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE,(IORD_ALTERA_AVALON_PIO_DATA(LEDG_BASE)^0x08));
        break;
        case 0x04:
            IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE,(IORD_ALTERA_AVALON_PIO_DATA(LEDG_BASE)^0x04));
        break;
        case 0x02:
            IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE,(IORD_ALTERA_AVALON_PIO_DATA(LEDG_BASE)^0x02));
        break;
    }

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, 0);                       // Write to the edge capture register to reset it.

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);
    /*
	Read the PIO to delay ISR exit. This is done to prevent a
    spurious interrupt in systems with high processor -> pio
    latency and fast interrupts.
    */
}

void SYS_Init(void)
{
    IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE,0);                           // Set LEDG=0
    Key_Interrupt_Init();
}

void Key_Interrupt_Init(void)
{
    void* edge_capture_ptr = (void*) &edge_capture_Key;					// Read the address of the edge_capture_Key.

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY_BASE,0x0E);                     // Enables interrupts for the corresponding PIO(KEY3,KEY2,KEY1) input port.
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


