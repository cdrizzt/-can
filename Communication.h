/**
  ******************************************************************************
  * @file    User/Communication.h
  * @author  KIKTechRobotics
  * @version V1.0.0
  * @date    29-June-2016
  * @brief   Header for Communication.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>

/*******************************************************************************
  * USART1:(Pin68,Pin69)---(PA9,PA10)---(USART1_TX,USART1_RX)---(FT,FT)
  * USART1:(Pin92,Pin93)---(PB6,PB7)----(USART1_TX,USART1_RX)---(FT,FT)---ok
  * USART2:(Pin25,Pin26)---(PA2,PA3)----(USART2_TX,USART2_RX)---(FT,FT)
  * USART2:(Pin86,Pin87)---(PD5,PD6)----(USART2_TX,USART2_RX)---(FT,FT)---ok
  * USART3:(Pin47,Pin48)---(PB10,PB11)--(USART3_TX,USART3_RX)---(FT,FT)---ok
	* USART3:(Pin78,Pin79)---(PC10,PC11)--(USART3_TX,USART3_RX)---(FT,FT)
  * UART4: (Pin23,Pin24)---(PA0,PA1)----(UART4_TX,UART4_RX)-----(FT,FT)
  * UART4: (Pin78,Pin79)---(PC10,PC11)--(UART4_TX,UART4_RX)-----(FT,FT)---ok
  * UART5: (Pin80,Pin83)---(PC12,PD2)---(UART5_TX,UART5_RX)-----(FT,FT)---ok
  * USART6:(Pin63,Pin64)---(PC6,PC7)----(USART6_TX,USART6_RX)---(FT,FT)---ok
*******************************************************************************/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#define RX4_SIZE 1024
extern unsigned char rx4_buf[RX4_SIZE];
extern unsigned int rx4_tail;
void USART1_Config(void);
void USART2_Config(void);
void USART3_Config(void);
void USART4_Config(void);
void UART4_Config(void);
void UART5_Config(void);
void USART6_Config(void);
void SendData(void);
void SendData2(void);
void SendData3(void);

#endif /* __COMMUNICATION_H */

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
