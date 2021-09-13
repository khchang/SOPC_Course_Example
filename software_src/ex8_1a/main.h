#ifndef MAIN_H_

#define MAIN_H_

#define SEGNUM          8

const unsigned char SEG7_Table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

volatile int edge_capture_Key;              //It is important that this be declared volatile to avoid unwanted compiler optimization.

void Key_Interrupt_Routine(void*);

void SYS_Init(void);
void SEG7_Clear(void);
void Key_Interrupt_Init(void);
void Key_Interrupt_Enable(void);
void Key_Interrupt_Disable(void);

#endif /*MAIN_H_*/
