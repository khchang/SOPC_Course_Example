/*
 * main.c
 *
 *      Author: kh
 */
#include <stdio.h>
#include <math.h>

#define     PI      3.1415925

int main(void)
{
    int i=0,j=0,SpaceNum;

    for(i=0;i<=20;i++)
    {
        SpaceNum=30+(int)(30*sin(i*PI/10));
        for(j=0;j<SpaceNum;j++)
        {
            printf(" ");
        }
        printf("*\n");
    }
    return 0;
}

