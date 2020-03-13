#ifndef __IMU_H
#define __IMU_H

#include "stdint.h"
typedef struct 
{
	union {int16_t Data; uint8_t data[2];}x; //源数据
	union {int16_t Data; uint8_t data[2];}y;
	union {int16_t Data; uint8_t data[2];}z;
	const float conversion_proportion;						//换算比例
	uint8_t flag;
	uint8_t time;														//判断时间
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
	int16_t Sampling_now;		//本次采样值
	int16_t Sampling_last;	//上次采样值
	int16_t filtration_last;//上次滤波值
	int16_t  filtration_now;//本次滤波值
	const float b;								//滤波系数
}High_pass;

typedef struct 
{
	int16_t Sampling_now;		//本次采样值
	int16_t filtration_last;//上次滤波值
	int16_t  filtration_now;//本次滤波值
	const float a;								//滤波系数
}low_pass;

void read_IMU(void);									 //读取IMU数据 未处理(需要旋转坐标以及除量程)
void imu_check(uint8_t check_time_max);//IMU检测  输入次数 可放入中断中
void IMU_Yaw(void);										 //imu积分计算偏航角 10ms计算一次

#endif
