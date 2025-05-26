#include "stm32f10x.h"   
#include "LED.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13);
}

void LED12_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
void LED12_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void LED12_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}


void LED13_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
void LED13_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void LED13_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	}
}

