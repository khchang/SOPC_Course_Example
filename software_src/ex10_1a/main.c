#include    <system.h>
#include    <stdio.h>
#include    <altera_avalon_pio_regs.h>
#include    <altera_avalon_uart_regs.h>
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

void UART_Interrupt(void *context)
{
    alt_u16 data, status;
    
    status = IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE);        // Read status Register of UART Core.
    
    while (!(status & ALTERA_AVALON_UART_STATUS_RRDY_MSK))      // Wait a newly received value is transferred into the rxdata register.
    {                                                           // When a newly received value is transferred into the rxdata register, RRDY is set to 1
        status = IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE);    // Read status register of UART Core.
    }
    
    data =IORD_ALTERA_AVALON_UART_RXDATA(RS232_BASE);           // Read rxdata register into data.

    //status = ALTERA_AVALON_UART_STATUS_TRDY_MSK;                // Set the TRDY for the status register.
    //IOWR_ALTERA_AVALON_UART_STATUS(RS232_BASE, status);
    
    IOWR_ALTERA_AVALON_UART_TXDATA(RS232_BASE, data);           // Write data to the txdata register.
    
    status = IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE);        // Read status Register of UART Core.
    
    while(!(status & ALTERA_AVALON_UART_STATUS_TRDY_MSK))
    {                                                           // When the txdata register is empty, it is ready for a new character, and TRDY is 1
        status = IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE);    // Read status register of UART Core.
    }
    
    
    //IOWR_ALTERA_AVALON_UART_STATUS(RS232_BASE, 0);              // Clear status register.
}

void SYS_Init(void)
{
    UART_Init();
}

void UART_Init(void)
{
    alt_u32 control;

    control = ALTERA_AVALON_UART_CONTROL_TRDY_MSK|ALTERA_AVALON_UART_CONTROL_RRDY_MSK|ALTERA_AVALON_UART_CONTROL_E_MSK;
    // Enable interupt for a tansmission ready.
    // Enable interrupt for a read ready.
    // Enable interrupt for an exception (TOE, ROE, BRK, FE, PE).

    IOWR_ALTERA_AVALON_UART_CONTROL(RS232_BASE, control);   // Write data to the control register of RS232_BASE

    //divisor = (int)(50000000/9600+0.5);
    //IOWR_ALTERA_AVALON_UART_DIVISOR(RS232_BASE, divisor);
    if (alt_ic_isr_register(RS232_IRQ_INTERRUPT_CONTROLLER_ID, RS232_IRQ, UART_Interrupt, NULL, 0x0))
    {
        printf("An error occurred during the registration of RS232 interrupt.\n\r");
    }
}

