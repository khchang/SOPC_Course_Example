/*
 * main.c
 *
 *      Author: kh
 */
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <alt_types.h>
#include <stdio.h>

int main(void)
{
		int i=0,j=0;
		unsigned char Led=0x01;
		unsigned char direction=0;
		while(1)
		{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, Led);
				if (direction==0)
				{
						Led<<=1;
				}
				else
				{
						Led>>=1;
				}
				if (Led==0x01)
				{
						direction=0;
				}
				else
				{
						if (Led==0x80)
						{
								direction=1;
						}
				}
				for(i=0;i<20;i++)
				{
						for(j=0;j<50000;j++);
				}
		}
		return 0;
}
