#ifndef MAIN_H_
#define MAIN_H_


alt_alarm alarm0;

void SYS_Init(void);
void Timer_Init(void);
void StrLCD_Init(void);
alt_u32 alarm0_callback(void*);

#endif /*MAIN_H_*/
