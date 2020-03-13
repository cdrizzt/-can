#include "Communication.h"

unsigned char rx4_buf[RX4_SIZE];
unsigned int rx4_tail=0;
#define BUFFER_SIZE 10
unsigned char aDST_Buffer[BUFFER_SIZE]= {'1','2','3','4','5','6','7','8'};

void USART6_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 14400;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART6, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART6, ENABLE);

    USART_ITConfig(USART6,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(USART6,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(USART6, USART_FLAG_TC);
}
void UART5_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(UART5, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(UART5, ENABLE);

    USART_ITConfig(UART5,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(UART5,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(UART5, USART_FLAG_TC);
}
void UART4_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级组
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(UART4, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(UART4, ENABLE);

    USART_ITConfig(UART4,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(UART4,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(UART4, USART_FLAG_TC);
}
void USART4_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级组
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Enable UART clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/* Connect PXx to USARTx_Tx*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);

	/* Connect PXx to USARTx_Rx*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

	/* Configure USART Tx as alternate function  */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure USART Rx as alternate function  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	DMA_InitTypeDef  DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx4_buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = (uint32_t)RX4_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream2, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream2, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART4, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(UART4, ENABLE);

	USART_ITConfig(UART4,USART_IT_TXE,DISABLE);//close start send interrupt 
	USART_ITConfig(UART4,USART_IT_TC,DISABLE);//close send end interrupt
	USART_ClearFlag(UART4, USART_FLAG_TC);

	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);  
}	
void USART3_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART_OverSampling8Cmd(USART3,DISABLE);
    //USART_OverSampling8Cmd(USART3,ENABLE);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART3, ENABLE);

    USART_ITConfig(USART3,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(USART3,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(USART3, USART_FLAG_TC);

//	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
//
//
//  DMA_InitTypeDef  DMA_InitStructure;
//
//  /* Enable DMA clock */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
//
//  /* Reset DMA Stream registers (for debug purpose) */
//  DMA_DeInit(DMA1_Stream3);
//
//  /* Configure DMA Stream */
//  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aDST_Buffer;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA1_Stream3, &DMA_InitStructure);
//
//	DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);
//
//  /* Enable DMA Stream Transfer Complete interrupt */
//  //DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
//
//  /* DMA Stream disable */
//  DMA_Cmd(DMA1_Stream3, DISABLE);
}
void USART2_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART2, ENABLE);

    USART_ITConfig(USART2,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(USART2,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(USART2, USART_FLAG_TC);

//	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
//
//
//  DMA_InitTypeDef  DMA_InitStructure;
//
//  /* Enable DMA clock */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
//
//  /* Reset DMA Stream registers (for debug purpose) */
//  DMA_DeInit(DMA1_Stream6);
//
//  /* Configure DMA Stream */
//  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aDST_Buffer;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA1_Stream6, &DMA_InitStructure);
//
//	DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);
//
//  /* Enable DMA Stream Transfer Complete interrupt */
//  //DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
//
//  /* DMA Stream disable */
//  DMA_Cmd(DMA1_Stream6, DISABLE);
}
void USART1_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef 	NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级组
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USARTx configured as follows:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART1, ENABLE);

    USART_ITConfig(USART1,USART_IT_TXE,DISABLE);//close start send interrupt
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);//close send end interrupt
    USART_ClearFlag(USART1, USART_FLAG_TC);

//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//
//
//  DMA_InitTypeDef  DMA_InitStructure;
//
//  /* Enable DMA clock */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//
//  /* Reset DMA Stream registers (for debug purpose) */
//  DMA_DeInit(DMA2_Stream7);
//
//  /* Configure DMA Stream */
//  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aDST_Buffer;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA2_Stream7, &DMA_InitStructure);
//
//	DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
//
//  /* Enable DMA Stream Transfer Complete interrupt */
//  //DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
//
//  /* DMA Stream disable */
//  DMA_Cmd(DMA2_Stream7, DISABLE);
}

void SendData(void)
{
    if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!= RESET)
    {
        DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
        DMA_Cmd(DMA2_Stream7, DISABLE);
    }

//	aDST_Buffer[0]++;
//	if(aDST_Buffer[0]>'9')
//		aDST_Buffer[0]='0';
//
//	aDST_Buffer[7]--;
//	if(aDST_Buffer[7]<'0')
//		aDST_Buffer[7]='9';
    DMA_Cmd(DMA2_Stream7, ENABLE);
}
void SendData2(void)
{
    if(DMA_GetFlagStatus(DMA1_Stream6,DMA_FLAG_TCIF6)!= RESET)
    {
        DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);
        DMA_Cmd(DMA1_Stream6, DISABLE);
    }

//	aDST_Buffer[0]++;
//	if(aDST_Buffer[0]>'9')
//		aDST_Buffer[0]='0';
//
//	aDST_Buffer[7]--;
//	if(aDST_Buffer[7]<'0')
//		aDST_Buffer[7]='9';
    DMA_Cmd(DMA1_Stream6, ENABLE);
}
void SendData3(void)
{
    if(DMA_GetFlagStatus(DMA1_Stream3,DMA_FLAG_TCIF3)!= RESET)
    {
        DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);
        DMA_Cmd(DMA1_Stream3, DISABLE);
    }
    aDST_Buffer[0]=0xA0;

    aDST_Buffer[1]=0x01;
    aDST_Buffer[2]=0x50;

    aDST_Buffer[3]=0x00;
    aDST_Buffer[4]=0x00;

    aDST_Buffer[5]=0x00;
    aDST_Buffer[6]=0x00;

    aDST_Buffer[7]=0x00;
    aDST_Buffer[8]=0x00;

    aDST_Buffer[9]=0xF1;

//	aDST_Buffer[0]++;
//	if(aDST_Buffer[0]>'9')
//		aDST_Buffer[0]='0';
//
//	aDST_Buffer[7]--;
//	if(aDST_Buffer[7]<'0')
//		aDST_Buffer[7]='9';
    DMA_Cmd(DMA1_Stream3, ENABLE);
}
/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
