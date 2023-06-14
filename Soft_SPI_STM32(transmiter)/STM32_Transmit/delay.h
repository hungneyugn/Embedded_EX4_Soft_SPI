#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
void TIM2_INT_Init(void);
void DelayMs(uint32_t ms);
void TIM2_IRQHandler(void);

#endif
