#ifndef __IMU_H
#define __IMU_H

#include "stdint.h"
typedef struct 
{
	union {int16_t Data; uint8_t data[2];}x; //Դ����
	union {int16_t Data; uint8_t data[2];}y;
	union {int16_t Data; uint8_t data[2];}z;
	const float conversion_proportion;						//�������
	uint8_t flag;
	uint8_t time;														//�ж�ʱ��
}IMU_SOURCE;

typedef struct
{
	IMU_SOURCE Gyro;
	IMU_SOURCE Acc;
	IMU_SOURCE Euler;
	//IMU_SOURCE Mag;
	uint8_t checksum;
	union {int16_t acc; uint8_t data[2];}Temperature;
}IMU_READ;

typedef struct 
{
	int16_t Sampling_now;		//���β���ֵ
	int16_t Sampling_last;	//�ϴβ���ֵ
	int16_t filtration_last;//�ϴ��˲�ֵ
	int16_t  filtration_now;//�����˲�ֵ
	const float b;								//�˲�ϵ��
}High_pass;

typedef struct 
{
	int16_t Sampling_now;		//���β���ֵ
	int16_t filtration_last;//�ϴ��˲�ֵ
	int16_t  filtration_now;//�����˲�ֵ
	const float a;								//�˲�ϵ��
}low_pass;

void read_IMU(void);									 //��ȡIMU���� δ����(��Ҫ��ת�����Լ�������)
void imu_check(uint8_t check_time_max);//IMU���  ������� �ɷ����ж���
void IMU_Yaw(void);										 //imu���ּ���ƫ���� 10ms����һ��

#endif
