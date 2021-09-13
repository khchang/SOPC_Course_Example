#include    <system.h>
#include    <stdio.h>
#include    <altera_avalon_pio_regs.h>
#include    <unistd.h>

int main(void)
{
    char* msg = "Hello World!";
    unsigned int counter = 0;
    FILE* fp;
    
    fp=fopen("/dev/rs232","w");
    if (fp!=NULL)
    {
        printf("/dev/rs232 opens success!\n\r");
        while(1)
        {
            fprintf(fp,"%s %u\n\r",msg,counter);
            IOWR(LEDR_BASE,0,IORD(LEDR_BASE,0)^0x3ffff);
            counter++;
            usleep(1*1000*1000);
        }
        fclose(fp);
    }
    else
    {
        printf("/dev/rs232 opens fail!\n\r");
    }
  return 0;
}
