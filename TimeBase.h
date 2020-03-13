/**
  ******************************************************************************
  * @file    User/TimeBase.h
  * @author  KIKTechRobotics
  * @version V1.0.0
  * @date    02-July-2016
  * @brief   Header for TimeBase.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMEBASE_H
#define __TIMEBASE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#define STOP_STORAGE_RACK_ROTATION   TIM_ITConfig(TIM1,TIM_IT_CC2, DISABLE)
#define START_STORAGE_RACK_ROTATION  TIM_ITConfig(TIM1,TIM_IT_CC2, ENABLE)

void TIM_Config(void);
void TIM_Config2(void);

#endif /* __TIMEBASE_H */

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
