#include    <system.h>
#include    <stdio.h>
#include    <altera_avalon_pio_regs.h>
#include    <unistd.h>

int main(void)
{
	unsigned int counter=0;

    while(1)
    {
        printf("Hello World! %u\n\r", counter);
        IOWR(LEDR_BASE,0,IORD(LEDR_BASE,0)^0x3ffff);
        counter++;
        usleep(1*1000*1000);
    }

  return 0;
}
