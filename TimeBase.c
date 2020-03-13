#include "TimeBase.h"

__IO uint16_t CCR1_Val = 40170;
__IO uint16_t CCR2_Val = 2000;
__IO uint16_t CCR3_Val = 13654;
__IO uint16_t CCR4_Val = 42480;//6826;
uint16_t PrescalerValue = 0;

/**
  * @brief  Configures the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级组
    /* Enable the TIM1 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* -----------------------------------------------------------------------
      TIM1 Configuration: Output Compare Timing Mode:

      In this example TIM1 input clock (TIM1CLK) is set to 2 * APB1 clock (PCLK1),
      since APB1 prescaler is different from 1.
        TIM1CLK = 2 * PCLK1
        PCLK1 = HCLK / 4
        => TIM1CLK = HCLK / 2 = SystemCoreClock /2

      To get TIM1 counter clock at 6 MHz, the prescaler is computed as follows:
         Prescaler = (TIM1CLK / TIM1 counter clock) - 1
         Prescaler = ((SystemCoreClock /2) /6 MHz) - 1

      CC1 update rate = TIM1 counter clock / CCR1_Val = 146.48 Hz
      ==> Toggling frequency = 73.24 Hz

      C2 update rate = TIM1 counter clock / CCR2_Val = 219.7 Hz
      ==> Toggling frequency = 109.8 Hz

      CC3 update rate = TIM1 counter clock / CCR3_Val = 439.4 Hz
      ==> Toggling frequency = 219.7 Hz

      CC4 update rate = TIM1 counter clock / CCR4_Val = 878.9 Hz
      ==> Toggling frequency = 439.4 Hz

      Note:
       SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
       Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
       function to update SystemCoreClock variable value. Otherwise, any configuration
       based on this variable will be incorrect.
    ----------------------------------------------------------------------- */


    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 2000000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM1, PrescalerValue, TIM_PSCReloadMode_Immediate);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);


    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);

    /* TIM1 enable counter */
    TIM_Cmd(TIM1, ENABLE);
}

void TIM_Config2(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* TIM1 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Enable the TIM1 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

    TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

    /* TIM1 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
