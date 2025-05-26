#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "LED.h"

uint16_t Action_Mode=0;
uint16_t SpeedDelay=200;
uint16_t SwingDelay=6;
uint16_t Face_Mode=0;
uint8_t WeiBa=0;
uint16_t Action;
void HouseAction_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//开启串口时钟
	//语音
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//默认PA9是USART1_TX的复用
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//复用上拉输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//默认PA9是USART1_RX的复用
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//蓝牙
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//默认PB10是USART3_TX的复用
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//复用上拉输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//默认PB11是USART3_RX的复用
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitTypeDef UASRT_InitStructure;//USART初始化
	UASRT_InitStructure.USART_BaudRate=9600;//波特率9600
	UASRT_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不需要硬件流控制
	UASRT_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//接受与发送均打开
	UASRT_InitStructure.USART_Parity=USART_Parity_No;//不需要奇偶校验
	UASRT_InitStructure.USART_StopBits=USART_StopBits_1;//停止位为1
	UASRT_InitStructure.USART_WordLength=USART_WordLength_8b;//字长8位
	USART_Init(USART1,&UASRT_InitStructure);
	USART_Init(USART3,&UASRT_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//语音接收中断配置，也就是如果接送到消息就直接中断
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//蓝牙接收中断配置，也就是如果接送到消息就直接中断
	
	//中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组2
	//语音中断配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//特定的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占式优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级为2
	NVIC_Init(&NVIC_InitStructure);
	//蓝牙中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;//特定的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占式优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级为2
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);//USART使能打开
	USART_Cmd(USART3,ENABLE);//USART使能打开
}

void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)//如果接受到
	{
		if(USART_ReceiveData(USART1)==0x01)//开灯
		{
			LED12_ON();
			LED13_ON();
			Action = 1 ;
		}
		if(USART_ReceiveData(USART1)==0x02)//关灯
		{
			LED12_OFF();
			LED13_OFF();
			Action = 2;
		}
		if(USART_ReceiveData(USART1)==0x03)//打开风扇
		{
			Action = 3;
		}
		if(USART_ReceiveData(USART1)==0x04)//风扇打开二档
		{
			Action = 4;
		}
		if(USART_ReceiveData(USART1)==0x05)//风扇打开三档
		{
			Action = 5;
		}
		if(USART_ReceiveData(USART1)==0x06)//关闭风扇
		{
			Action = 6;
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	
}
//作者是Sngels_wyh只在抖音与B站
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)//如果接受到
	{
		if(USART_ReceiveData(USART3)==0x29)//放松的趴下
		{
			
		}
		
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
	//作者是Sngels_wyh只在抖音与B站
}
