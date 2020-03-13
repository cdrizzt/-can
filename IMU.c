#include "IMU.h"
#include "HardwareSerial.h"
#include "string.h"
#include "headfile.h"
#define g 9.8
IMU_READ imu_read={.Gyro.conversion_proportion=2000,
									 .Acc.conversion_proportion=156.8,
									 .Euler.conversion_proportion=180};

/*-------------------------------------------------------------------------------------------------------------------
  @brief      初始化加速度计
  @return     void   
  @input      void
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void IMU_init(void)//初始化加速度计
{
	uint8_t Data[5]={0};
	//加速度计矫正 初始化加速度计
	Data[0]=0xff;
	Data[1]=0xAA;
	Data[2]=0x01;
	Data[3]=0x01;
	Data[4]=0x00;
	for(int i=0;i<=4;i++)
		Serial_write(Data[i]);
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief      输入角度   
  @return     void   
  @input      Roll Pitch Yaw  int_16
  @since      v1.0
  Notes: IMU_angle_init(0,0,0);  //输入到陀螺仪内
--------------------------------------------------------------------------------------------------------------------*/
void IMU_angle_init(int16_t Roll,int16_t Pitch,int16_t Yaw)//角度赋值
{
	uint8_t Data[5]={0};
	Data[0]=0xFF;
	Data[1]=0xAA;
	//Roll赋值
	Data[2]=0x3d;
	Data[3]=Roll;
	Data[4]=Roll>>8;
	for(int i=0;i<=4;i++)
		Serial_write(Data[i]);
	//Pitch
	Data[2]=0x3e;
	Data[3]=Pitch;
	Data[4]=Pitch>>8;
	for(int i=0;i<=4;i++)
		Serial_write(Data[i]);
	
	//Pitch
	Data[2]=0x3f;
	Data[3]=Yaw;
	Data[4]=Yaw>>8;
	for(int i=0;i<=4;i++)
		Serial_write(Data[i]);
	
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      转换imu单位   //加入高通滤波器
  @return     void   
  @input      void
  @since      v1.1
	Notes: 			ax=imu.acc/32768*16*9.8  Company: m/s^2
--------------------------------------------------------------------------------------------------------------------*/
void IMU_conversion(IMU_SOURCE *read,IMU *write,uint8_t mode)
{
		if(mode==0x52)
			write->Angle_Velocity=-(float)(read->z.Data)*read->conversion_proportion/32768;
//	static High_pass high_pass_x={0,0,0,0,0.85};
//	static High_pass high_pass_y={0,0,0,0,0.85};
//	static High_pass high_pass_z={0,0,0,0,1};
//	
//	High_pass_filtering(&high_pass_x,imu.wx.dps);
//	High_pass_filtering(&high_pass_y,imu.wy.dps);
//	High_pass_filtering(&high_pass_z,imu.wz.dps);
	
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      读取角度原始数据  
  @return     void   
  @input      void
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void read_IMU_source(IMU_SOURCE *source,uint8_t *data)//读取IMU
{
	source->x.data[0]=*(data+1);
	source->x.data[1]=*(data+2);
	source->y.data[0]=*(data+3);
	source->y.data[1]=*(data+4);
	source->z.data[0]=*(data+5);
	source->z.data[1]=*(data+6);
	source->time=0;
	source->flag=1;
	IMU_conversion(source,&Robot.imu,*data);
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      读取角度  
  @return     void   
  @input      void
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void read_IMU(void)//读取IMU
{
		static uint8_t Data[15]={0};
		static uint8_t DataNum=0;
		static uint8_t read_flag=0;
		register uint8_t check_sum=0;
		if (IMU_AVAILABLE())
		{
				Data[DataNum]=IMU_READ();
				if(!read_flag)
				{
					if(Data[DataNum]==IMU_HEAD)
					{
						DataNum++;
						read_flag=1;
					}
					else
						DataNum=0;
				}
				else
				{
						if(DataNum<10)
						{
							DataNum++;
						}
						else
						{
								read_flag=0;
							  imu_read.checksum=Data[DataNum];
								for(register int i=0;i<=10;i++) check_sum=Data[i];
								if(imu_read.checksum==check_sum)
								{
											if(Data[1]==0x51)//加速度
											{
												read_IMU_source(&imu_read.Acc,(Data+1));
											}
											else if(Data[1]==0x53)//欧拉角
											{
													read_IMU_source(&imu_read.Euler,(Data+1));
											}	
											else if(Data[1]==0x52)//陀螺仪
											{
													read_IMU_source(&imu_read.Gyro,(Data+1));
											}
											else
											{
												WARRING_FLAG=1;
												WARRING_NUM[1]=1;
											}
											DataNum=0;
											memset(Data, 0, sizeof(Data));
											imu_read.checksum=0;
								}
								else
								{
										WARRING_FLAG=1;
										WARRING_NUM[2]=1;
										memset(Data, 0, sizeof(Data));
										DataNum=0;
								}
						}
				}
		}
}			
/*-------------------------------------------------------------------------------------------------------------------
  @brief      imu检测  
  @return     void   
  @input      time  10ms
  @since      v1.0
  Notes: 			放在中断里  
--------------------------------------------------------------------------------------------------------------------*/
void imu_check(uint8_t check_time_max)//检查imu是否正常
{
		imu_read.Acc.time++;
		imu_read.Gyro.time++;
		//imu_read.Euler.time++;
		if(imu_read.Gyro.time++>=check_time_max)
		{
				WARRING_FLAG=1;
				WARRING_NUM[3]=1;
		}
		if(imu_read.Acc.time>=check_time_max)
		{
				WARRING_FLAG=1;
				WARRING_NUM[4]=1;
		}
		if(imu_read.Euler.time>=check_time_max)
		{
				WARRING_FLAG=1;
				WARRING_NUM[5]=1;
		}
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief      高通滤波器  
  @return     void   
  @input      high_pass
  @since      v1.0
  Notes: 			陀螺仪滤波
--------------------------------------------------------------------------------------------------------------------*/
void High_pass_filtering(High_pass *h,int16_t filtration_now)
{
	h->filtration_now=filtration_now;
	h->Sampling_now=h->b*(h->filtration_now-h->filtration_last+h->Sampling_last);
	
	//return h->Sampling_now;
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      低通滤波
  @return     void   
  @input      high_pass
  @since      v1.0
  Notes: 			加速度和磁力计滤波
--------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------------------
  @brief      角速度积分计算角度
  @return     void   
  @input      void
  @since      v1.1
	Notes: 			ax=imu.acc/32768*16*9.8  Company: m/s^2
--------------------------------------------------------------------------------------------------------------------*/
void IMU_Yaw(void)
{
	if(imu_read.Gyro.flag==1)
	{
		static float YAW=0,yaw=0;
		YAW+=Robot.imu.Angle_Velocity/100;
		yaw+=Robot.odomter.Angle_Velocity/100;
		imu_read.Gyro.flag=0;
	}
}
