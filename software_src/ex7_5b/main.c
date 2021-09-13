#include    "system.h"
#include    "altera_avalon_pio_regs.h"
#include    "sys/alt_irq.h"
#include    "main.h"

int main(void)
{
    SYS_Init();
    while(1)
    {
    }
    return 0;    
}

void SW_Interrupt_Routine(void* context)
{
    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Cast context to edge_capture's type. It is important that this
    be declared volatile to avoid unwanted compiler optimization. */

    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE);       // Read SW_BASE's edgecapture register.

    if(*edge_capture_ptr&0x3ffff)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE,IORD_ALTERA_AVALON_PIO_DATA(SW_BASE));    // Read SW and write to LEDR
    }

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE, 0);                        // Reset SW_BASE edgecapture register.
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE);
    /*
	Read the PIO to delay ISR exit. This is done to prevent a
    spurious interrupt in systems with high processor -> pio
    latency and fast interrupts.
    */
}

void SYS_Init(void)
{
    IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE,IORD_ALTERA_AVALON_PIO_DATA(SW_BASE));    // Read SW and write to LEDR
    SW_Interrupt_Init();
}

void SW_Interrupt_Init(void)
{
    void* edge_capture_ptr = (void*) &edge_capture_SW;					// Read the address of the edge_capture_SW.
        
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SW_BASE,0x3FFFF);					// Enables interrupts for the corresponding PIO(SW[17..0]) input port.
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE,0);							// Reset the edge capture register.
    alt_ic_isr_register(SW_IRQ_INTERRUPT_CONTROLLER_ID, SW_IRQ, SW_Interrupt_Routine, edge_capture_ptr, 0x0);	// Register a SW ISR.
    SW_Interrupt_Enable();                                              // Enable ISR.
}

void SW_Interrupt_Enable(void)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE, 0);						// Reset SW_BASE edgecapture register.
    alt_ic_irq_enable(SW_IRQ_INTERRUPT_CONTROLLER_ID, SW_IRQ);			// Enable SW_IRQ interrupt function.
}

void SW_Interrupt_Disable(void)
{
	alt_ic_irq_disable(SW_IRQ_INTERRUPT_CONTROLLER_ID, SW_IRQ);			// Disable SW_IRQ interrupt function.
}
