/**
  ******************************************************************************
  * @file    User/HardwareSerial.h
  * @author  KIKTechRobotics
  * @version V1.0.0
  * @date    30-June-2016
  * @brief   Header for HardwareSerial.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARESERIAL_H
#define __HARDWARESERIAL_H

/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"

#define true 1
#define false 0
#define SERIAL_BUFFER_SIZE 1024

typedef struct
{
    unsigned char buffer[SERIAL_BUFFER_SIZE];
    unsigned int head;
    unsigned int tail;
} ring_buffer;

void store_char(unsigned char c, ring_buffer *buffer);

unsigned int Serial_available(void);
unsigned int Serial2_available(void);
unsigned int Serial3_available(void);
unsigned int Serial4_available(void);
unsigned int Serial5_available(void);
unsigned int Serial6_available(void);

int Serial_read(void);
int Serial2_read(void);
int Serial3_read(void);
int Serial4_read(void);
int Serial5_read(void);
int Serial6_read(void);

unsigned char Serial_write(unsigned char c);
unsigned char Serial2_write(unsigned char c);
unsigned char Serial3_write(unsigned char c);
unsigned char Serial4_write(unsigned char c);
unsigned char Serial5_write(unsigned char c);
unsigned char Serial6_write(unsigned char c);



#endif /* __HARDWARESERIAL_H */

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
