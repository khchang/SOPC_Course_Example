/*
 * main.c
 *
 *      Author: kh
 */
#include <stdio.h>

int main()
{
    unsigned int i=0,j=0;

    for(i=1;i<=5;i++)
    {
        for(j=0;j<i;j++)
        {
            printf("%c",'A'+j);
        }
        printf("\n");
    }

  return 0;
}


