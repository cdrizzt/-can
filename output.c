#include "output.h"
#include "HardwareSerial.h" 
#include "headfile.h"
#include "stdio.h"
#include "string.h"
uint8_t send_flag=0;
/*-------------------------------------------------------------------------------------------------------------------
  @brief      输出到示波器
  @return     void   
  @input      void
  @since      v1.1
	Notes: 			输入输出数组以及 数量
--------------------------------------------------------------------------------------------------------------------*/
void Oscillograph_out(int16_t a[17],uint8_t num)
{
    uint8_t cmd=0x03;

    Serial_write(cmd);
    Serial_write(~cmd);
    for(int i=0; i<num; i++)
    {
        Serial_write(a[i]);
        Serial_write(a[i]>>8);
    }

    Serial_write(~cmd);
    Serial_write(cmd);
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief      错误打印
  @return     void   
  @input      void
  @since      v1.1
	Notes: 			WARRING[]  ERROR[]  //警告车子会继续运行  错误则直接暂停
--------------------------------------------------------------------------------------------------------------------*/
uint8_t WARRING_FLAG=0;
uint8_t WARRING_NUM[255]={0};
uint8_t ERROR_FLAG=0;
void Error_out()
{
		if(WARRING_FLAG)
		{
			if(WARRING_NUM[0])
				  printf("camera check error\n");
			if(WARRING_NUM[1])
					printf("imu set error\n");
			if(WARRING_NUM[2])
					printf("imu checksum error\n");
			if(WARRING_NUM[3])
					printf("Gyro lose\n");
			if(WARRING_NUM[4])
					printf("acc lose\n");
			if(WARRING_NUM[5])
					printf("euler lose\n");
			
			WARRING_FLAG=0;
			memset(WARRING_NUM,0,sizeof(WARRING_NUM));
		}
		if(ERROR_FLAG)
		{
			
		}
}
