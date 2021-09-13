#include    "system.h"
#include    "altera_avalon_pio_regs.h"
#include    "main.h"

int main(void)
{
    unsigned int SW=0;
    while(1)
    {
        SW=IORD_ALTERA_AVALON_PIO_DATA(SW_BASE);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE,SW);
    }
    return 0;    
}
