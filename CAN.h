#ifndef __CAN_H
#define __CAN_H
#include "stdint.h"



uint8_t CAN1_Init(uint8_t brp);            //CAN�����ʷ�Ƶ
uint8_t CAN1_irq_Init(uint8_t brp);				 //CAN�ж϶�
uint8_t CAN_Send(uint8_t *buf,uint8_t len,uint8_t num); //��������
int32_t CAN_read(uint8_t *buf,uint8_t len,uint8_t num);
#endif
