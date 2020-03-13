/********************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    22-April-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"
#include "HardwareSerial.h"
#include "Encoder.h"
#include "stdlib.h"
#include "IMU.h"
#include "Speed.h"
#include "output.h"
#include "headfile.h"
#include "Odometer.h"
extern volatile uint32_t _millis;
extern ring_buffer rx_buffer;
extern ring_buffer tx_buffer;

extern ring_buffer rx_buffer2;
extern ring_buffer tx_buffer2;

extern ring_buffer rx_buffer3;
extern ring_buffer tx_buffer3;

extern ring_buffer rx_buffer4;
extern ring_buffer tx_buffer4;

extern ring_buffer rx_buffer5;
extern ring_buffer tx_buffer5;

extern ring_buffer rx_buffer6;
extern ring_buffer tx_buffer6;

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

extern __IO uint16_t TIM9_CCR1_Val;
extern __IO uint16_t TIM9_CCR2_Val;

extern uint32_t EncodeSpeedL;
extern uint32_t EncodeSpeedR;
extern uint32_t EncodeSpeedM;


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    _millis++;
}

void TIM1_CC_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
				IMU_Yaw();
				imu_check(20);
				Odometer_Velocity(&Robot.odomter);
				static uint16_t i=0;
				static uint8_t time_i=0;
				if(time_i%2==0)
				{
					i++;
					if(i>500)
					{
						time_i++;
					}
				}
				else 
				{
					i--;
					if(i==0)
						time_i++;
				}
				if(time_i>10)
				{
					i=0;
				}
				Speed_out(-i,i);
//				Right+=((float)(Right_pulse)/6000);
//				Left+=((float)(Left_pulse)/6000);


				if(send_flag==1)
				{
						int16_t a[17]={0};
						a[0]=(int16_t)(Robot.odomter.Angle_Velocity*10);
						a[1]=(int16_t)(Robot.imu.Angle_Velocity*10);
						a[2]=(int16_t)(Robot.odomter.Left_pulse.Revs);
						a[3]=(int16_t)(Robot.odomter.Right_pulse.Revs);
						a[4]=i;
						Oscillograph_out(a,5);
				}

        /**********************************/
        capture = TIM_GetCapture1(TIM1);
        TIM_SetCompare1(TIM1, capture + CCR1_Val);

    }
}


void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

        capture = TIM_GetCapture1(TIM2);
        TIM_SetCompare1(TIM2, capture + CCR1_Val);
    }
}

/**
  * @brief  This function handles TIM9 global interrupt request.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(USART1);
        store_char(c, &rx_buffer);
    }
    if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
    {
        if (tx_buffer.head == tx_buffer.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer.buffer[tx_buffer.tail];
            tx_buffer.tail = (tx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(USART1, c);
        }
    }
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(USART2);
        store_char(c, &rx_buffer2);
    }
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {
        if (tx_buffer2.head == tx_buffer2.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer2.buffer[tx_buffer2.tail];
            tx_buffer2.tail = (tx_buffer2.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(USART2, c);
        }
    }
}

/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(USART3);
        store_char(c, &rx_buffer3);
    }
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
    {
        if (tx_buffer3.head == tx_buffer3.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer3.buffer[tx_buffer3.tail];
            tx_buffer3.tail = (tx_buffer3.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(USART3, c);
        }
    }
}

/**
  * @brief  This function handles UART4 global interrupt request.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(UART4);
        store_char(c, &rx_buffer4);
    }
    if(USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
    {
        if (tx_buffer4.head == tx_buffer4.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer4.buffer[tx_buffer4.tail];
            tx_buffer4.tail = (tx_buffer4.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(UART4, c);
        }
    }
}

/**
  * @brief  This function handles UART5 global interrupt request.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(UART5);
        store_char(c, &rx_buffer5);
    }
    if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
    {
        if (tx_buffer5.head == tx_buffer5.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer5.buffer[tx_buffer5.tail];
            tx_buffer5.tail = (tx_buffer5.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(UART5, c);
        }
    }
}

/**
  * @brief  This function handles USART6 global interrupt request.
  * @param  None
  * @retval None
  */
void USART6_IRQHandler(void)
{
    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
    {
        unsigned char c = USART_ReceiveData(USART6);
        store_char(c, &rx_buffer6);
    }
    if(USART_GetITStatus(USART6, USART_IT_TXE) != RESET)
    {
        if (tx_buffer6.head == tx_buffer6.tail) {
            // Buffer empty, so disable interrupts
            USART_ITConfig(USART6, USART_IT_TXE, DISABLE);
        }
        else {
            // There is more data in the output buffer. Send the next byte
            unsigned char c = tx_buffer6.buffer[tx_buffer6.tail];
            tx_buffer6.tail = (tx_buffer6.tail + 1) % SERIAL_BUFFER_SIZE;

            USART_SendData(USART6, c);
        }
    }
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
