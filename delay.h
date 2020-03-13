/**
  ******************************************************************************
  * @file    User/delay.h
  * @author  KIKTechRobotics
  * @version V1.0.0
  * @date    29-June-2016
  * @brief   Header for delay.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

void Delay_Init(void);
static inline uint32_t micros(void);
uint32_t millis(void);
void delayMicroseconds(uint32_t n);
void delay(uint32_t n);

#endif /* __DELAY_H */

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
