#include "can.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "Speed.h"
#include "headfile.h"
//CAN��ʼ��

//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//������Ϊ:42M/((6+7+1)*3)=1Mbps

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
  @brief      can���߳�ʼ��	
  @return     void   
  @input      brp �������� 12->250k
  @since      v1.0
	Notes: 			baudrate:250Kbps=42MHz/((6+7+1)*12)(Forklift)
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CAN1_Init(uint8_t brp)
{
    GPIO_InitTypeDef       GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);//ʹ��CAN1ʱ��

    //��ʼ��GPIO
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11|GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //����
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //��ʼ��PA11,PA12

    //���Ÿ���ӳ������
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1

    //CAN��Ԫ����
    CAN_InitStructure.CAN_TTCM = DISABLE;	        //��ֹʱ�䴥��ͨ��ģʽ��CANӲ���������������ڷ���/������������ʱ�����
    CAN_InitStructure.CAN_ABOM = DISABLE;	        //����Զ����߹���CANӲ�������߹ر�ʱ��״̬��
    CAN_InitStructure.CAN_AWUM = DISABLE;         //0��˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)��1��˯��ģʽӲ�����ѡ�
    CAN_InitStructure.CAN_NART = ENABLE;	        //0��CANӲ�����Զ��ط���ֱ���ɹ���1����ֹ�����Զ����ͣ�ֻ��1�Σ�
    CAN_InitStructure.CAN_RFLM = DISABLE;	        //0��FIFO�������������,�µĸ��Ǿɵģ�1��FIFO�����������������1������ʧ��
    CAN_InitStructure.CAN_TXFP = DISABLE;	        //0�����ȼ��ɱ��ı�ʶ��������1�����ȼ�������˳�������
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //����ģʽ
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	    //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ 1tq ~ 4tq��λ�仯�ڴ˽׶η�����
    CAN_InitStructure.CAN_BS1  = CAN_BS1_7tq;     //Tbs1��Χ 1tq ~ 16tq������������λ�ã�
    CAN_InitStructure.CAN_BS2  = CAN_BS2_6tq;     //Tbs2��Χ 1tq ~ 8tq�������巢�͵��λ�ã�
    CAN_InitStructure.CAN_Prescaler = brp;        //��Ƶϵ��(Fdiv)Ϊbrp+1������Ԥ�ʷ�Ƶ1-1024��
    CAN_Init(CAN1, &CAN_InitStructure);           // ��ʼ��CAN1

    //���ù�����
    CAN_FilterInitStructure.CAN_FilterNumber=0;	                       //������0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;     //32λ
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                   //32λID
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;               //32λMASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //������0������FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //���������0
    CAN_FilterInit(&CAN_FilterInitStructure);                          //�˲�����ʼ��

    return 0;
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief      can���߳�ʼ��	�ж�(�������ж�)
  @return     void   
  @input      brp �������� 12->250k
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
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�������ȼ���
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//��1?��PORTA����?��	                   											 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);//��1?��CAN1����?��	

		//3?��??��GPIO
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11|GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //?�䨮?1|?��
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //��?������?3?
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //��?��-
		GPIO_Init(GPIOA, &GPIO_InitStructure);                   //3?��??��PA11,PA12

		//��y???�䨮?��3��?????
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11?�䨮??aCAN1
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12?�䨮??aCAN1

		//CAN�̣�?a����??
		CAN_InitStructure.CAN_TTCM = DISABLE;	        //???1����??�䣤���騪��D??�꨺?�ꡧCAN��2?t??��y?��?��??��?��������?��/?������??����2����?����??�䨢��?
		CAN_InitStructure.CAN_ABOM = DISABLE;	        //����?t��??����???1�������ꡧCAN��2?t?������??1?��?������?���䨬?��?	  
		CAN_InitStructure.CAN_AWUM = DISABLE;         //0��o?��???�꨺?����1y����?t??D?(??3yCAN->MCR��?SLEEP??)��?1��o?��???�꨺?��2?t??D??��
		CAN_InitStructure.CAN_NART = ENABLE;	        //0��oCAN��2?t??��??��??�����??����?3��1|��?1��o???1����??��??����??���ꡧ??����1��?��?
		CAN_InitStructure.CAN_RFLM = DISABLE;	        //0��oFIFO����??��?3?o��2????��,D?��??2???����?��?1��oFIFO����??��?3?o��???����???1��????a����?��
		CAN_InitStructure.CAN_TXFP = DISABLE;	        //0��o��??��??��������??������?��????����?1��o��??��??����???��?3D��???��?��
		CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //?y3��?�꨺?
		CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	    //??D?��?2?��????��?��(Tsjw)?atsjw+1??����??�̣�?? 1tq ~ 4tq�ꡧ??��??��?����??��??���騦����?
		CAN_InitStructure.CAN_BS1  = CAN_BS1_7tq;     //Tbs1��??�� 1tq ~ 16tq�ꡧ?����?2��?����?��?????��?
		CAN_InitStructure.CAN_BS2  = CAN_BS2_6tq;     //Tbs2��??�� 1tq ~ 8tq��?�ꡧ?����?����?����?��?????��?
		CAN_InitStructure.CAN_Prescaler = brp;        //��??��?�̨�y(Fdiv)?abrp+1�ꡧ2����??��?����??��1-1024��?	
		CAN_Init(CAN1, &CAN_InitStructure);           // 3?��??��CAN1
		
		//????1y???��
		CAN_FilterInitStructure.CAN_FilterNumber=0;	                       //1y???��0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;     //32?? 
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                   //32??ID
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;               //32??MASK
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //1y???��01?��a��?FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //?��??1y???��0
		CAN_FilterInit(&CAN_FilterInitStructure);                          //??2��?��3?��??��		
		
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
		
	 return 0;
}



//can����һ������(�̶���ʽ:IDΪ0X0101,��׼֡,����֡)
//len:���ݳ���(���Ϊ8)
//msg:����ָ��,���Ϊ8���ֽ�.
//uint8_t can_1read()
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can����
	@return     uint 8 �����Ƿ�ɹ�   
	@input      Data[len] len numҪ���͵�IP
  @since      v1.0
	Notes: 			baudrate:250Kbps=42MHz/((6+7+1)*12)(Forklift)
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CAN_Send(uint8_t *buf,uint8_t len,uint8_t num)
{
    uint8_t mail;
    uint16_t i=0;

    CanTxMsg TxMessage;    //CAN���Ͷ���
    //D0-D7 >0���㲥ģʽ��1-255�����ձ����ߵ�ջ�ţ���
    //D8 >0:�㲥/����ģʽ��1���㵽��ģʽ;
    //D9-D10 >:����Ȩ��
		if(num==1)
		{
			TxMessage.StdId = 0x0101;	         // ��׼��ʶ��ID��11λ:D0-D10;D0-D7:0(�㲥ģʽ)1-255�����ձ����ߵ�ջ�ţ���
			TxMessage.ExtId = 0x0101;	         // ��չ��ʾ��ID��29λ��
		}
		else if(num==2)
		{
			TxMessage.StdId = 0x0102;	         // ��׼��ʶ��ID��11λ��
			TxMessage.ExtId = 0x0102;	         // ��չ��ʾ��ID��29λ��
		}
		else
		{
				printf("can num error");
				return 0;
		}
    TxMessage.IDE = CAN_Id_Standard; // ʹ�ñ�׼��
    TxMessage.RTR = CAN_RTR_Data;		 // ��Ϣ����Ϊ����֡��/ң��֡
    TxMessage.DLC = len;		         // ���ĳ���
    for(i=0; i<len; i++)
        TxMessage.Data[i]=buf[i];				 // ��һ֡��Ϣ

    mail = CAN_Transmit(CAN1, &TxMessage);
    i=0;
    while((CAN_TransmitStatus(CAN1, mail)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
    if(i>=0XFFF)return 1;
    return 0;
		
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can����
	@return     Data int32
  @input      ip �������� 
  @since      v1.0
	Notes: 			��һλָ��0A ����0B  ��λָ��0D����ֵ0E
--------------------------------------------------------------------------------------------------------------------*/
int32_t CAN_read(uint8_t *buf,uint8_t len,uint8_t num)
{
	CanRxMsg RxMessage;
	int32_t Data=0;
	while(RxMessage.Data[0]!=num)//���ص����ݱ����Ҫ�������һ��
	{
		while(CAN_Send(buf,len,num));
		for(uint16_t i=2500;i>0;i--);
		CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
		if(RxMessage.Data[0]==0)
			break;
	}
	if((RxMessage.Data[1]==0x0B&&*(buf+1)==0x0A)||(RxMessage.Data[1]==0x0E&&*(buf+1)==0x0D))//��ȷ��
	{
			if(RxMessage.DLC==6)//16λ����
				Data=(int16_t)(RxMessage.Data[4]<<8)|(RxMessage.Data[5]);
			else if(RxMessage.DLC==8)//32λ����
				Data=(RxMessage.Data[6]<<24)|(RxMessage.Data[7]<<16)|(RxMessage.Data[4]<<8)|(RxMessage.Data[5]);
			return Data;
	}
	return 0;
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      can�ж�
	@return     Data int32
  @input      ip �������� 
  @since      v1.0
	Notes: 			stdIdΪ���淽ID  Data: 0->���շ�ID 1->������(0XC9) 2->�Ĵ�����ַ
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
