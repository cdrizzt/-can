#ifndef __CAMERA_H
#define __CAMERA_H

#include "stdint.h"
#include "headfile.h"
typedef struct 
{
	union {int16_t Data; uint8_t data[2];}ordinate; //Ô´Êý¾Ý
	union {int16_t Data; uint8_t data[2];}abscissa;
	union {int16_t Data; uint8_t data[2];}angle;
}CAMERA_DATA;


typedef struct 
{
	CAMERA_DATA UP;
	CAMERA_DATA DOWM;
	uint8_t checksum;
}CAMERA;



void read_camera(void);
void camera_position(CAMERA_DATA *c,POSITION *r,DIRECTION *d);
	
#endif
