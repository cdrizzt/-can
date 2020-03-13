#include "Encoder.h"

#define ENCODER_RIGHT_TIMER   TIM3  				// Right Encoder unit connected to TIM3
#define ENCODER_RIGHT_PPR     (u16)(2000)   	// number of pulses per revolution
#define ENCODER_LEFT_TIMER   	TIM5  				// Left Encoder unit connected to TIM5
#define ENCODER_LEFT_PPR     	(u16)(2000)   	// number of pulses per revolution
#define ENCODER_MOTOR_TIMER   TIM4  				// Motor Encoder unit connected to TIM4
#define ENCODER_MOTOR_PPR     (u16)(2000)   	// number of pulses per revolution
#define ENCODER_TEST_TIMER   	TIM2  				// Test Encoder unit connected to TIM2
#define ENCODER_TEST_PPR     	(u16)(2000)   	// number of pulses per revolution

/*******************************************************************************
* Function Name  : ENC_RIGHT_INIT
* Description    : General Purpose Timer x set-up for encoder speed/position
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_RIGHT_INIT(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM3 clock source enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* Enable GPIOC, clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    /* Configure PC6,PC7 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);

    /* Enable the TIM3 Update Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

    /* Timer configuration in Encoder mode */
    TIM_DeInit(ENCODER_RIGHT_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x00; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_RIGHT_PPR)-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_RIGHT_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_RIGHT_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(ENCODER_RIGHT_TIMER, &TIM_ICInitStructure);

    // Clear all pending interrupts
    TIM_ClearFlag(ENCODER_RIGHT_TIMER, TIM_FLAG_Update);
    //TIM_ITConfig(ENCODER_RIGHT_TIMER, TIM_IT_Update, ENABLE);
    //Reset counter
    ENCODER_RIGHT_TIMER->CNT = 0x00;

    TIM_Cmd(ENCODER_RIGHT_TIMER, ENABLE);
}
/*******************************************************************************
* Function Name  : GET_ENC_RIGHT
* Description    : Get the Counter Register value
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t GET_ENC_RIGHT(void)
{
    uint32_t a=TIM_GetCounter(ENCODER_RIGHT_TIMER);
    TIM_SetCounter(ENCODER_RIGHT_TIMER, 0);

    return   a;

    //return TIM_GetCounter(ENCODER_RIGHT_TIMER);
}
/*******************************************************************************
* Function Name  : ENC_RIGHT_INIT
* Description    : General Purpose Timer x set-up for encoder speed/position
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_LEFT_INIT(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM5 clock source enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    /* Enable GPIOA, clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    /* Configure PC6,PC7 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);

    /* Enable the TIM3 Update Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

    /* Timer configuration in Encoder mode */
    TIM_DeInit(ENCODER_LEFT_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x00; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_LEFT_PPR)-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_LEFT_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_LEFT_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(ENCODER_LEFT_TIMER, &TIM_ICInitStructure);

    // Clear all pending interrupts
    TIM_ClearFlag(ENCODER_LEFT_TIMER, TIM_FLAG_Update);
    //TIM_ITConfig(ENCODER_LEFT_TIMER, TIM_IT_Update, ENABLE);
    //Reset counter
    ENCODER_LEFT_TIMER->CNT = 0x00;

    TIM_Cmd(ENCODER_LEFT_TIMER, ENABLE);
}
/*******************************************************************************
* Function Name  : GET_ENC_LEFT
* Description    : Get the Counter Register value
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t GET_ENC_LEFT(void)
{
    uint32_t a=TIM_GetCounter(ENCODER_LEFT_TIMER);
    TIM_SetCounter(ENCODER_LEFT_TIMER, 0);
    return   a;
}
/*******************************************************************************
* Function Name  : ENC_MOTOR_INIT
* Description    : General Purpose Timer x set-up for encoder speed/position
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_MOTOR_INIT(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM3 clock source enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    /* Enable GPIOD, clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    /* Configure PC6,PC7 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

    /* Enable the TIM3 Update Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

    /* Timer configuration in Encoder mode */
    TIM_DeInit(ENCODER_MOTOR_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x00; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_MOTOR_PPR)-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_MOTOR_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_MOTOR_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(ENCODER_MOTOR_TIMER, &TIM_ICInitStructure);

    // Clear all pending interrupts
    TIM_ClearFlag(ENCODER_MOTOR_TIMER, TIM_FLAG_Update);
    //TIM_ITConfig(ENCODER_MOTOR_TIMER, TIM_IT_Update, ENABLE);
    //Reset counter
    ENCODER_MOTOR_TIMER->CNT = 0x00;

    TIM_Cmd(ENCODER_MOTOR_TIMER, ENABLE);
}
/*******************************************************************************
* Function Name  : GET_ENC_MOTOR
* Description    : Get the Counter Register value
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t GET_ENC_MOTOR(void)
{
    uint32_t a=TIM_GetCounter(ENCODER_MOTOR_TIMER);
    TIM_SetCounter(ENCODER_MOTOR_TIMER, 0);
    return   a;
}
/*******************************************************************************
* Function Name  : ENC_TEST_INIT
* Description    : General Purpose Timer x set-up for encoder speed/position
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_TEST_INIT(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM3 clock source enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    /* Enable GPIOA, clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable GPIOB, clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    /* Configure PA15 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PB3 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);

    /* Enable the TIM3 Update Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

    /* Timer configuration in Encoder mode */
    TIM_DeInit(ENCODER_MOTOR_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x00; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_MOTOR_PPR)-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_TEST_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_TEST_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(ENCODER_TEST_TIMER, &TIM_ICInitStructure);

    // Clear all pending interrupts
    TIM_ClearFlag(ENCODER_TEST_TIMER, TIM_FLAG_Update);
    //TIM_ITConfig(ENCODER_TEST_TIMER, TIM_IT_Update, ENABLE);
    //Reset counter
    ENCODER_TEST_TIMER->CNT = 0x00;

    TIM_Cmd(ENCODER_TEST_TIMER, ENABLE);
}
/*******************************************************************************
* Function Name  : GET_ENC_TEST
* Description    : Get the Counter Register value
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t GET_ENC_TEST(void)
{
    return TIM_GetCounter(ENCODER_TEST_TIMER);
}

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
