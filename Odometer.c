#include "Odometer.h"
#include "arm_math.h"
#include "fast_atan.h"
/*-------------------------------------------------------------------------------------------------------------------
  @brief      通过里程计获得的角速度和线速度
	@return     void 
  @input      void
  @since      v1.0
	Notes: 			传入 ODOMETER
--------------------------------------------------------------------------------------------------------------------*/
void Odometer_Velocity(ODOMETER *odo)
{	
	int16_t change_pulse = (odo->Left_pulse.Revs)-(odo->Right_pulse.Revs);
	float average_pulse=(float)(odo->Left_pulse.Revs+odo->Right_pulse.Revs)/2;
	float Perimeter=odo->WheelDiameter*PI;
	odo->Line_Velocity=average_pulse*Perimeter/60/odo->Reduction_ratio;
	odo->Angle_Velocity=((float)(change_pulse)*odo->WheelDiameter*3)/(odo->Reduction_ratio*odo->Wheelbase);
	
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief      根据里程计计算机器人坐标
	@return     void 
  @input      传入机器人里程计计算线速度及角速度
  @since      v1.0
	Notes: 			传入 ODOMETER
--------------------------------------------------------------------------------------------------------------------*/
void Odomet_opsition(POSITION *robot,ODOMETER *odo)
{
		float change_x=0;
		float change_y=0;
	
		robot->Yaw+=odo->Angle_Velocity;
		change_x = odo->Line_Velocity * arm_cos_f32(robot->Yaw);
		change_y = odo->Line_Velocity * arm_sin_f32(robot->Yaw);
		
		robot->x+=change_x;
		robot->y+=change_y;
}

