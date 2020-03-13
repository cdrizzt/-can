#ifndef __CAN_H
#define __CAN_H
#include "stdint.h"



uint8_t CAN1_Init(uint8_t brp);            //CAN波特率分频
uint8_t CAN1_irq_Init(uint8_t brp);				 //CAN中断读
uint8_t CAN_Send(uint8_t *buf,uint8_t len,uint8_t num); //发送数据
int32_t CAN_read(uint8_t *buf,uint8_t len,uint8_t num);
#endif
