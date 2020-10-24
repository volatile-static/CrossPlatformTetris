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
 ALIENTEK��ӢSTM32������ʵ��11
 ���ݴ�������ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
  TPAD_Init(6);			//��ʼ����������
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
 		if(TPAD_Scan(0))	//�ɹ�������һ��������(�˺���ִ��ʱ������15ms)
		{
			LED1=!LED1;		//LED1ȡ��
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
	delay_ms(10);//����
	if(KEY1==0)	 //����KEY1
	{				 
		LED0=!LED0;
		MoveRight(&Messenger);
		Upd();
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(WK_UP==1)	 	 //WK_UP����
	{				 
		LED1=!LED1;
		Transform(&Messenger);
		Upd();	
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 

//�ⲿ�ж�3�������


void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0)	 //����KEY0
	{
		MoveLeft(&Messenger);
		Upd();
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
 
