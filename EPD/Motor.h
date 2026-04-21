#ifndef _Motor_
#define _Motor_
#include "gd32l23x.h"
void Motor(void);
void Motor1(void);
void Motor2(void);
void Motor3(void);
void Clock_Motor(void);
void Motor_Timer2_Init(uint32_t step_hz);
#endif