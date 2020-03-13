#include "Speed.h"
#include "CAN.h"
#include "headfile.h"
#include "math.h"
/*-------------------------------------------------------------------------------------------------------------------
  @brief      输出速度 
	@return     void 
  @input      int16_t 不大于3600转 电机转速
  @since      v1.0
	Notes: 			
--------------------------------------------------------------------------------------------------------------------*/
void Speed_out(int16_t Right_out,int16_t Left_out)
{
		uint8_t left_can[6] = {0x00, 0x54, 0x00, 0x00, 0x00, 0xC8};	//200
		uint8_t right_can[6] = {0x00, 0x54, 0x00, 0x00, 0x00, 0xC8};	//200
		
		left_can[4]=Left_out>>8;
		left_can[5]=Left_out;
		right_can[4]=Right_out>>8;
		right_can[5]=Right_out;
		CAN_Send(left_can,6,1);
		CAN_Send(right_can,6,2);
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief      读取脉冲 
	@return     void 
  @input      void
  @since      v1.0
	Notes: 			//不使用，使用can中断读取脉冲
--------------------------------------------------------------------------------------------------------------------*/
void Speed_read(void)
{

}



