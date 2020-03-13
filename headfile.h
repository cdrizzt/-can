#ifndef __HEADFILE_H
#define __HEADFILE_H
#include "stdint.h"

#define PI 3.141592f
#define TURE 1
#define FLASE 0

#define CAMERA_READ() Serial6_read()
#define CAMERA_AVAILABLE() Serial6_available()
#define CAMERA_HEAD_ST 0x55
#define CAMERA_HEAD_ER 0xAA
#define CAMERA_ERROR 	 0x8f

#define IMU_READ() Serial4_read()
#define IMU_AVAILABLE() Serial4_available()
#define IMU_HEAD 0x55

typedef struct
{
  float Angle_Velocity;		//imu的角速度
	float Line_Velocity;		//imu的线速度速度
}IMU;

typedef struct
{
	union {int16_t Revs; uint8_t data[2];}Right_pulse;
	union {int16_t Revs; uint8_t data[2];}Left_pulse;
	const float Wheelbase;				//轴距
	const float WheelDiameter;		//直径
	const int16_t Reduction_ratio;//减速比
	float Angle_Velocity;		//odometer的角速度
	float Line_Velocity;		//odometer的线速度速度
	
}ODOMETER;//主动轮

typedef struct
{
  float x;
	float y;
	float Yaw;
}POSITION;

typedef struct
{
	IMU imu;
	ODOMETER odomter;
	POSITION camera;
	POSITION Position_Reality;
}ROBOT;//机器人

extern ROBOT Robot;

typedef enum
{ 
  EAST 	 = 90,
  SOUTH  = 180, 
  WEST   = -90, 
  NORTH  = 0  
}DIRECTION;

extern uint8_t WARRING_FLAG;
extern uint8_t WARRING_NUM[255];
extern uint8_t ERROR_FLAG;


#endif
