#ifndef MAIN_H_
#define MAIN_H_


#define StopWatch_Stop          1
#define StopWatch_Running       2


volatile int edge_capture_Key;              //It is important that this be declared volatile to avoid unwanted compiler optimization.
unsigned int status=0;

alt_alarm alarm0;
struct timeval stopwatch_timer;

void Key_Interrupt_Routine(void*);
void SYS_Init(void);
void Timer_Init(void);
void StrLCD_Init(void);
void Key_Interrupt_Init(void);
void Key_Interrupt_Enable(void);
void Key_Interrupt_Disable(void);
alt_u32 alarm0_callback(void*);
void Display_Stop_Watch_Time(void);

#endif /*MAIN_H_*/
