/*
 * main.h
 *
 *      Author: kh
 */

#ifndef __MAIN_H_
#define __MAIN_H_

volatile int edge_capture_Key;              //It is important that this be declared volatile to avoid unwanted compiler optimization.

void Key_Interrupt_Routine(void*);
void SYS_Init(void);
void Key_Interrupt_Init(void);
void Key_Interrupt_Enable(void);
void Key_Interrupt_Disable(void);



#endif /* MAIN_H_ */
