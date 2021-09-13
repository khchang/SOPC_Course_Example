#include    <system.h>
#include    <stdio.h>
#include    <altera_avalon_pio_regs.h>
#include    <unistd.h>

int main(void)
{
    char return_sentence[31], receive_char;
    unsigned int i=0;
    printf("\n\r");
    while(1)
    {
        printf("Please enter a sentence after press Enter: ");
        i=0;
        do
        {
            receive_char=getchar();
            return_sentence[i]=receive_char;
            i++;
        }
        while((receive_char!='\r')&&(i<30));
        return_sentence[i]='\0';                                // The End character of the sentence.
        printf("\n\r");
        printf("You just enter the sentence: %s\n\r",return_sentence);
        printf("\n\r");
        IOWR(LEDR_BASE,0,IORD(LEDR_BASE,0)^0x3ffff);
        usleep(1*500*1000);
    }

  return 0;
}
