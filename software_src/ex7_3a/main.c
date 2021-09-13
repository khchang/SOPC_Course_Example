/*
 * main.c
 *
 *      Author: kh
 */
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include <stdio.h>

int main(void)
{
    int i=0,j=0;

    while(1)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0x15555);
        for(i=0;i<20;i++)
        {
            for(j=0;j<50000;j++);
        }
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0x2aaaa);
        for(i=0;i<20;i++)
        {
            for(j=0;j<50000;j++);
        }
    }
    return 0;
}


