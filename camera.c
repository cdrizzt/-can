#include "camera.h"
#include "HardwareSerial.h"
#include "string.h"

CAMERA camera_data={0};
/*-------------------------------------------------------------------------------------------------------------------
  @brief      д������ͷ����
  @return     void   
  @input      void
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void read_camera_data(CAMERA_DATA *c,uint8_t *data)
{
	c->angle.data[1]=*(data+2);
	c->angle.data[0]=*(data+3);
	c->abscissa.data[1]=*(data+4);
	c->abscissa.data[0]=*(data+5);
	c->ordinate.data[1]=*(data+6);
	c->ordinate.data[0]=*(data+7);
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      ��ȡ����ͷ�������򼰽Ƕ�
  @return     void   
  @input      void
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void read_camera()
{
	static uint8_t data[20]={0};
	static uint8_t DataNum =0;
	static uint8_t read_flag=0;
  register uint8_t check_sum=0;
	if(CAMERA_AVAILABLE())
	{
		if(!read_flag)
		{
				data[DataNum]=CAMERA_READ();
				if(DataNum>0 && !read_flag && data[DataNum-1]==CAMERA_HEAD_ST && data[DataNum]==CAMERA_HEAD_ER)
				{
					read_flag=1;
					DataNum++;
				}
				else if(!read_flag && DataNum>0)
				{
					data[DataNum-1]=data[DataNum];
				}
				else
					DataNum++;
		}
		else
		{
			data[DataNum]=CAMERA_READ();
			if(DataNum<14)
				DataNum++;
			else
			{
				camera_data.checksum=data[14];
				for(register uint8_t i=0;i<=13;i++)check_sum+=data[i];
				if(check_sum==camera_data.checksum)
				{
						if(data[2]!=CAMERA_ERROR && data[3]!=CAMERA_ERROR)
								read_camera_data(&camera_data.DOWM,data);
						if(data[8]!=CAMERA_ERROR && data[9]!=CAMERA_ERROR)
								read_camera_data(&camera_data.UP,data);
						
						memset(data,0,sizeof(data));
						read_flag=0;
						DataNum=0;
				}
				else
				{
						WARRING_FLAG=1;
						WARRING_NUM[0]=1;
						memset(data,0,sizeof(data));
						read_flag=0;
						DataNum=0;
				}
			}
		}
	}
}
/*-------------------------------------------------------------------------------------------------------------------
  @brief      ��������ͷӳ��Ƕ�(����ɫ����㵱ǰ����������)
  @return     void   
  @input      ����ͷ���ݣ�����������ͷ���꣬0�㷽��
  @since      v1.0
  Notes: 
--------------------------------------------------------------------------------------------------------------------*/
void camera_position(CAMERA_DATA *c,POSITION *r,DIRECTION *d)
{
	float angle=((float)(c->angle.Data))/16;
	float abscissa=((float)(c->abscissa.Data))/1000;
	float ordinate=((float)(c->ordinate.Data))/1000;
	
	
}
