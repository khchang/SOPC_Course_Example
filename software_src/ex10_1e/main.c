#include    <system.h>
#include    <stdio.h>
#include    <altera_avalon_pio_regs.h>
#include    <unistd.h>

int main(void)
{
    char return_sentence[31], receive_char;
    unsigned int i=0;
    FILE* fp;
    
    fp=fopen("/dev/rs232","w+");
    if (fp!=NULL)
    {
        printf("/dev/rs232 opens success!\n\r");
        fprintf(fp,"\n\r");
        while(1)
        {
            fprintf(fp,"Please enter a sentence after press Enter: ");
            i=0;
            do
            {
                receive_char=fgetc(fp);
                return_sentence[i]=receive_char;
                i++;
            }
            while((receive_char!='\r')&&(i<30));
            return_sentence[i]='\0';                                // The End character of the sentence.
            fprintf(fp,"\n\r");
            fprintf(fp,"You just enter the sentence: %s\n\r",return_sentence);
            fprintf(fp,"\n\r");
            IOWR(LEDR_BASE,0,IORD(LEDR_BASE,0)^0x3ffff);
            usleep(1*500*1000);
        }
        fclose(fp);
    }
    else
    {
        printf("/dev/rs232 opens fail!\n\r");
    }

  return 0;
}
