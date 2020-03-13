/**
  ******************************************************************************
  * @file    User/Encoder.h
  * @author  KIKTechRobotics
  * @version V1.0.0
  * @date    29-June-2016
  * @brief   Header for Encoder.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_H
#define __ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/*******************************************************************************
  * Quadrature (Incremental) Encoder:TIM2,TIM3,TIM4,TIM5
  * ENCODER1:(Pin23,Pin24)---(PA0,PA1)---(TIM5_CH1,TIM5_CH2)(FT,FT)---ok
  * ENCODER2:(Pin31,Pin32)---(PA6,PA7)---(TIM3_CH1,TIM3_CH2)(FT,FT)
  * ENCODER3:(Pin59,Pin60)---(PD12,PD13)-(TIM4_CH1,TIM4_CH2)(FT,FT)---ok
  * ENCODER4:(Pin63,Pin64)---(PC6,PC7)---(TIM3_CH1,TIM3_CH2)(FT,FT)
  * ENCODER5:(Pin90,Pin91)---(PB4,PB5)---(TIM3_CH1,TIM3_CH2)(FT,FT)---ok
  * ENCODER6:(Pin92,Pin93)---(PB6,PB7)---(TIM4_CH1,TIM4_CH2)(FT,FT)
  * ENCODER7:(Pin77,Pin89)---(PA15,PB3)--(TIM2_CH1,TIM2_CH2)(FT,FT)---ok
*******************************************************************************/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ENC_RIGHT_INIT(void);
void ENC_LEFT_INIT(void);
void ENC_MOTOR_INIT(void);
void ENC_TEST_INIT(void);
uint32_t GET_ENC_RIGHT(void);
uint32_t GET_ENC_LEFT(void);
uint32_t GET_ENC_MOTOR(void);
uint32_t GET_ENC_TEST(void);

#endif /* __ENCODER_H */

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
