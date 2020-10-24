#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "tpad.h"
#include "exti.h"
#include "lcd.h"
#include "remote.h"
#include "Tetris.h"
#include "beep.h"
#include <stdlib.h>

/************************************************
 ALIENTEK精英STM32开发板实验11
 电容触摸按键实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 TCmd Messenger;
 int CurrCol = GREEN;
void Upd(void) {
	u8 i;
	for (i = 0; i < Messenger.cnt[0]; ++i) {
		LCD_Fill(Messenger.Erase[i].X * 10, Messenger.Erase[i].Y * 10, Messenger.Erase[i].X * 10 + 10, Messenger.Erase[i].Y * 10 + 10, WHITE);
	}
	for (i = 0; i < Messenger.cnt[1]; ++i) {
		LCD_Fill(Messenger.Paint[i].X * 10, Messenger.Paint[i].Y * 10, Messenger.Paint[i].X * 10 + 10, Messenger.Paint[i].Y * 10 + 10, CurrCol);
	}
	
}
 int main(void)
 {	
 	u8 key;  	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
  TPAD_Init(6);			//初始化触摸按键
	EXTIX_Init();
	 Remote_Init();
	 LCD_Init();
	 srand(233);
	 NewGame(&Messenger);
	 Upd();
   	while(1)
	{					
		delay_ms(666);
			key=Remote_Scan();//98 168 34 194
		switch (key) {
			case 98:
				Transform(&Messenger);
				Upd();
				break;
			case 34:
				MoveLeft(&Messenger);
			Upd();
			break;
			
			case 194:
				MoveRight(&Messenger);
			Upd();
			break;
		}
		if(!MoveDown(&Messenger)){
			switch (rand() % 6) {
				case 0:
					CurrCol = GREEN;
				break;
				case 1:
					CurrCol = BROWN;
				break;
				case 2:
					CurrCol = BLACK;
				break;
				case 3:
					CurrCol = YELLOW;
				break;
				case 4:
					CurrCol = RED;
				break;
				case 5:
					CurrCol = BLUE;
				break;
			}
			Upd();
			continue;
		}
 		if(TPAD_Scan(0))	//成功捕获到了一次上升沿(此函数执行时间至少15ms)
		{
			LED1=!LED1;		//LED1取反
		}
		if (GameOver()) {
			LCD_Clear(WHITE);
			NewGame(&Messenger);
		}
		Upd();
	}
 }

void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键KEY1
	{				 
		LED0=!LED0;
		MoveRight(&Messenger);
		Upd();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(WK_UP==1)	 	 //WK_UP按键
	{				 
		LED1=!LED1;
		Transform(&Messenger);
		Upd();	
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 

//外部中断3服务程序


void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==0)	 //按键KEY0
	{
		MoveLeft(&Messenger);
		Upd();
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
 
