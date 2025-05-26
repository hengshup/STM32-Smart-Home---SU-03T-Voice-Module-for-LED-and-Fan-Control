#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HouseAction.h"
#include "Servo.h"
#include "LED.h"
#include "Motor.h"


//指令：唤醒指令：你好小智
// 开灯、关灯、打开风扇、风扇打开二档、风扇打开三档、关闭风扇...


int main(void)
{
	HouseAction_Init();                                                                                                                                             
	OLED_Init(); 
	LED_Init();
	Motor_Init();
	while(1)
	{	
		
		if(Action == 1)
		{
			OLED_ShowString(1,1,"               ");
			OLED_ShowString(2,1,"               ");
			OLED_ShowString(1,1,"Open LED12");
			OLED_ShowString(2,1,"Open LED13");
			Delay_ms(2000);
		}
		if(Action == 2)
		{
			OLED_ShowString(1,1,"               ");
			OLED_ShowString(2,1,"               ");
			OLED_ShowString(1,1,"close LED12");
			OLED_ShowString(2,1,"close LED13");
			Delay_ms(2000);
		}
		if(Action == 3)
		{
			Motor_SetSpeed(30); //一档
			OLED_ShowString(3,1,"                  ");
			OLED_ShowString(3,1,"Open air fan one");
			Delay_ms(1000);
		}
		if(Action == 4)
		{
			Motor_SetSpeed(60); //二档
			OLED_ShowString(3,1,"                  ");
			OLED_ShowString(3,1,"Open air fan tow");
			Delay_ms(1000);
		}
		if(Action == 5)
		{
			Motor_SetSpeed(90); //三档
			OLED_ShowString(3,1,"                  ");
			OLED_ShowString(3,1,"Open air fan three");
			Delay_ms(1000);
		}
		if(Action == 6)
		{
			Motor_SetSpeed(0);
			OLED_ShowString(3,1,"                  ");
			OLED_ShowString(3,1,"close air fan ");
			Delay_ms(1000);
		}
	}
}
