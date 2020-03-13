#include "can.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "Speed.h"
#include "headfile.h"
//CAN初始化

//波特率=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//则波特率为:42M/((6+7+1)*3)=1Mbps

//uint8_t  can1_buf1[8]={0x00,0x1E,0x00,0x10,0x00,0x00};          /rvo disable
//uint8_t  can1_buf2[8]={0x00,0x1E,0x00,0x10,0x00,0x01};          /rvo enable
//uint8_t  can1_buf1[8]={0x00,0x1E,0x00,0x10,0x00,0x00};          /rvo disable
//uint8_t can1_buf02[8]={0x00,0x1E,0x00,0x10,0x00,0x01};          //servo enable
//uint8_t can1_buf03[8]={0x00,0x3C,0x00,0x64,0x00,0x00,0xC3,0x50};//100mm@50000pluse(position mode)
//uint8_t can1_buf04[8]={0x00,0x3C,0x00,0x64,0x00,0x00,0x75,0x30};//100mm@30000pluse(position mode)
//unt8_t can1_buf05[6]={0x00,0x28,0x00,0x00,0x00,0x01};					 //100rpm(speed mode)
//uint8_t can1_buf06[6]={0x00,0x28,0x00,0x00,0x00,0xC8};					 //200rpm(speed mode)
//uint8_t can1_buf07[6]={0x00,0x28,0x00,0x01,0x00,0x0A};					 //0.01%(torque mode)
//uint8_t can1_buf08[6]={0x00,0x28,0x00,0x01,0x00,0x64};					 //0.10%(torque mode)
//uint8_t can1_buf09[8]={0x00,0x2B,0x00,0x02,0x00,0x0A,0x00,0x0A}; //0.01%(absolute mode)
//uint8_t can1_buf10[8]={0x00,0x2B,0x00,0x02,0x00,0x64,0x00,0x0A}; //0.10%(absolute mode)
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can总线初始化	
  @return     void   
  @input      brp 传送速率 12->250k
  @since      v1.0
	Notes: 			baudrate:250Kbps=42MHz/((6+7+1)*12)(Forklift)
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CAN1_Init(uint8_t brp)
{
    GPIO_InitTypeDef       GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能PORTA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);//使能CAN1时钟

    //初始化GPIO
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11|GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //初始化PA11,PA12

    //引脚复用映射配置
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11复用为CAN1
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12复用为CAN1

    //CAN单元设置
    CAN_InitStructure.CAN_TTCM = DISABLE;	        //禁止时间触发通信模式（CAN硬件计数器激活用于发送/接邮箱生产的时间戳）
    CAN_InitStructure.CAN_ABOM = DISABLE;	        //软件自动离线管理（CAN硬件在总线关闭时的状态）
    CAN_InitStructure.CAN_AWUM = DISABLE;         //0：睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)；1：睡眠模式硬件唤醒。
    CAN_InitStructure.CAN_NART = ENABLE;	        //0：CAN硬件将自动重发，直到成功；1：禁止报文自动传送（只发1次）
    CAN_InitStructure.CAN_RFLM = DISABLE;	        //0：FIFO报文溢出后不锁定,新的覆盖旧的；1：FIFO报文溢出后锁定，下1条将丢失。
    CAN_InitStructure.CAN_TXFP = DISABLE;	        //0：优先级由报文标识符决定；1：优先级由请求顺序决定。
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //正常模式
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	    //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 1tq ~ 4tq（位变化在此阶段发生）
    CAN_InitStructure.CAN_BS1  = CAN_BS1_7tq;     //Tbs1范围 1tq ~ 16tq（定义采样点的位置）
    CAN_InitStructure.CAN_BS2  = CAN_BS2_6tq;     //Tbs2范围 1tq ~ 8tq６（定义发送点的位置）
    CAN_InitStructure.CAN_Prescaler = brp;        //分频系数(Fdiv)为brp+1（波特预率分频1-1024）
    CAN_Init(CAN1, &CAN_InitStructure);           // 初始化CAN1

    //配置过滤器
    CAN_FilterInitStructure.CAN_FilterNumber=0;	                       //过滤器0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;     //32位
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                   //32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;               //32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //激活过滤器0
    CAN_FilterInit(&CAN_FilterInitStructure);                          //滤波器初始化

    return 0;
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief      can总线初始化	中断(带接收中断)
  @return     void   
  @input      brp 传送速率 12->250k
  @since      v1.0
	Notes: 			baudrate:250Kbps=42MHz/((6+7+1)*12)(Forklift)
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CAN1_irq_Init(uint8_t brp)
{
    GPIO_InitTypeDef       GPIO_InitStructure; 
		CAN_InitTypeDef        CAN_InitStructure;
		CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		NVIC_InitTypeDef 	NVIC_InitStructure;

		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级组
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ê1?üPORTAê±?ó	                   											 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);//ê1?üCAN1ê±?ó	

		//3?ê??ˉGPIO
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11|GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //?′ó?1|?ü
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //í?íìê?3?
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //é?à-
		GPIO_Init(GPIOA, &GPIO_InitStructure);                   //3?ê??ˉPA11,PA12

		//òy???′ó?ó3é?????
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11?′ó??aCAN1
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12?′ó??aCAN1

		//CANμ￥?aéè??
		CAN_InitStructure.CAN_TTCM = DISABLE;	        //???1ê±??′￥·￠í¨D??￡ê?￡¨CANó2?t??êy?÷?¤??ó?óú·￠?í/?óóê??éú2úμ?ê±??′á￡?
		CAN_InitStructure.CAN_ABOM = DISABLE;	        //èí?t×??ˉà???1üàí￡¨CANó2?t?ú×ü??1?±?ê±μ?×′ì?￡?	  
		CAN_InitStructure.CAN_AWUM = DISABLE;         //0￡o?ˉ???￡ê?í¨1yèí?t??D?(??3yCAN->MCRμ?SLEEP??)￡?1￡o?ˉ???￡ê?ó2?t??D??￡
		CAN_InitStructure.CAN_NART = ENABLE;	        //0￡oCANó2?t??×??ˉ??·￠￡??±μ?3é1|￡?1￡o???1±¨??×??ˉ′??í￡¨??·￠1′?￡?
		CAN_InitStructure.CAN_RFLM = DISABLE;	        //0￡oFIFO±¨??ò?3?oó2????¨,D?μ??2???éμ?￡?1￡oFIFO±¨??ò?3?oó???¨￡???1ì????aê§?￡
		CAN_InitStructure.CAN_TXFP = DISABLE;	        //0￡oó??è??óé±¨??±êê?·????¨￡?1￡oó??è??óé???ó?3Dò???¨?￡
		CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //?y3￡?￡ê?
		CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	    //??D?í?2?ì????í?è(Tsjw)?atsjw+1??ê±??μ￥?? 1tq ~ 4tq￡¨??±??ˉ?ú′??×??·￠éú￡?
		CAN_InitStructure.CAN_BS1  = CAN_BS1_7tq;     //Tbs1·??§ 1tq ~ 16tq￡¨?¨ò?2é?ùμ?μ?????￡?
		CAN_InitStructure.CAN_BS2  = CAN_BS2_6tq;     //Tbs2·??§ 1tq ~ 8tq￡?￡¨?¨ò?·￠?íμ?μ?????￡?
		CAN_InitStructure.CAN_Prescaler = brp;        //·??μ?μêy(Fdiv)?abrp+1￡¨2¨ì??¤?ê·??μ1-1024￡?	
		CAN_Init(CAN1, &CAN_InitStructure);           // 3?ê??ˉCAN1
		
		//????1y???÷
		CAN_FilterInitStructure.CAN_FilterNumber=0;	                       //1y???÷0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;     //32?? 
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                   //32??ID
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;               //32??MASK
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //1y???÷01?áaμ?FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //?¤??1y???÷0
		CAN_FilterInit(&CAN_FilterInitStructure);                          //??2¨?÷3?ê??ˉ		
		
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
		
	 return 0;
}



//can发送一组数据(固定格式:ID为0X0101,标准帧,数据帧)
//len:数据长度(最大为8)
//msg:数据指针,最大为8个字节.
//uint8_t can_1read()
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can发送
	@return     uint 8 发送是否成功   
	@input      Data[len] len num要发送的IP
  @since      v1.0
	Notes: 			baudrate:250Kbps=42MHz/((6+7+1)*12)(Forklift)
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CAN_Send(uint8_t *buf,uint8_t len,uint8_t num)
{
    uint8_t mail;
    uint16_t i=0;

    CanTxMsg TxMessage;    //CAN发送定义
    //D0-D7 >0：广播模式；1-255：接收报告者的栈号）；
    //D8 >0:广播/报告模式；1：点到点模式;
    //D9-D10 >:优先权；
		if(num==1)
		{
			TxMessage.StdId = 0x0101;	         // 标准标识符ID（11位:D0-D10;D0-D7:0(广播模式)1-255（接收报告者的栈号））
			TxMessage.ExtId = 0x0101;	         // 扩展标示符ID（29位）
		}
		else if(num==2)
		{
			TxMessage.StdId = 0x0102;	         // 标准标识符ID（11位）
			TxMessage.ExtId = 0x0102;	         // 扩展标示符ID（29位）
		}
		else
		{
				printf("can num error");
				return 0;
		}
    TxMessage.IDE = CAN_Id_Standard; // 使用标准贞
    TxMessage.RTR = CAN_RTR_Data;		 // 消息类型为数据帧；/遥控帧
    TxMessage.DLC = len;		         // 报文长度
    for(i=0; i<len; i++)
        TxMessage.Data[i]=buf[i];				 // 第一帧信息

    mail = CAN_Transmit(CAN1, &TxMessage);
    i=0;
    while((CAN_TransmitStatus(CAN1, mail)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
    if(i>=0XFFF)return 1;
    return 0;
		
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can接收
	@return     Data int32
  @input      ip 返回数据 
  @since      v1.0
	Notes: 			读一位指令0A 返回0B  两位指令0D返回值0E
--------------------------------------------------------------------------------------------------------------------*/
int32_t CAN_read(uint8_t *buf,uint8_t len,uint8_t num)
{
	CanRxMsg RxMessage;
	int32_t Data=0;
	while(RxMessage.Data[0]!=num)//返回的数据必须跟要求的数据一致
	{
		while(CAN_Send(buf,len,num));
		for(uint16_t i=2500;i>0;i--);
		CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
		if(RxMessage.Data[0]==0)
			break;
	}
	if((RxMessage.Data[1]==0x0B&&*(buf+1)==0x0A)||(RxMessage.Data[1]==0x0E&&*(buf+1)==0x0D))//正确码
	{
			if(RxMessage.DLC==6)//16位数据
				Data=(int16_t)(RxMessage.Data[4]<<8)|(RxMessage.Data[5]);
			else if(RxMessage.DLC==8)//32位数据
				Data=(RxMessage.Data[6]<<24)|(RxMessage.Data[7]<<16)|(RxMessage.Data[4]<<8)|(RxMessage.Data[5]);
			return Data;
	}
	return 0;
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can中断
	@return     Data int32
  @input      ip 返回数据 
  @since      v1.0
	Notes: 			stdId为报告方ID  Data: 0->接收方ID 1->功能码(0XC9) 2->寄存器地址
--------------------------------------------------------------------------------------------------------------------*/
void CAN1_RX0_IRQHandler()
{
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	if(RxMessage.RTR == CAN_RTR_Remote)
	{
		//u8 Canbuf[8]={0};
	}
	else if(RxMessage.RTR == CAN_RTR_Data)
	{
		if(RxMessage.Data[1]==0xC9&&RxMessage.Data[2]==0x00)
		{
				if(RxMessage.StdId==0x00000601)
				{
						Robot.odomter.Left_pulse.data[1]=RxMessage.Data[4];
						Robot.odomter.Left_pulse.data[0]=RxMessage.Data[5];
				}
				else if(RxMessage.StdId==0x00000602)
				{
						Robot.odomter.Right_pulse.data[1]=RxMessage.Data[4];
						Robot.odomter.Right_pulse.data[0]=RxMessage.Data[5];
				}
		}
		//process received data in here!
		
	}
}
