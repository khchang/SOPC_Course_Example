#ifndef MAIN_H_
#define MAIN_H_

volatile int edge_capture_SW;              //It is important that this be declared volatile to avoid unwanted compiler optimization.

void SW_Interrupt_Routine(void*);
void SYS_Init(void);
void SW_Interrupt_Init(void);
void SW_Interrupt_Enable(void);
void SW_Interrupt_Disable(void);

#endif /*MAIN_H_*/
