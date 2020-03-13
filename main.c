/**
******************************************************************************
* @file    Project/STM32F4xx_StdPeriph_Templates/main.c
* @author  MCD Application Team
* @version V1.7.0
* @date    22-April-2016
* @brief   Main program body
****************  **************************************************************
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

#include "main.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include "Encoder.h"
#include "Communication.h"
#include "HardwareSerial.h"
#include "delay.h"
#include "TimeBase.h"
#include "IMU.h"
#include "CAN.h"
#include "headfile.h"
#include "output.h"
/* Private typedef -----------------------------------------------------------*/
void Delay(__IO uint32_t nCount) {
    while(nCount--) {
    }
}

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

//	Serial_write(ch);
    return ch;
}
ROBOT Robot={	.imu={0}, .Position_Reality={0},
.odomter.Wheelbase=70.0,.odomter.WheelDiameter=17.0,
.odomter.Reduction_ratio=20};
											 
void Hardware()
{

    Delay_Init();
    USART1_Config();//wifi
		USART4_Config(); 
		CAN1_irq_Init(6);
		//CAN1_Init(6);//3
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		//USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    TIM_Config();
}
//					GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);//红
//					GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_RESET);//绿
//					GPIO_WriteBit(GPIOA,GPIO_Pin_10,Bit_RESET);//蓝

int main(void)
{
    Hardware();
    while(1)
    {
				read_IMU();
			
				static unsigned long previousMillis1;//
        static unsigned long currentMillis1;
        currentMillis1 = millis();
        if(currentMillis1 - previousMillis1 >= 1000)
					Error_out();

		}
}
