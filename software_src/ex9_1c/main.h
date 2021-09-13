#ifndef MAIN_H_
#define MAIN_H_

#define SEGNUM          8
#define Timer_Clock     50e6

const unsigned char SEG7_Table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

alt_alarm alarm0;

void SYS_Init(void);
void Timer_Init(void);
void SEG7_Clear(void);
alt_u32 alarm0_callback(void*);

#endif /*MAIN_H_*/