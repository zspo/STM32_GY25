#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"

//ALIENTEK Mini STM32�����巶������3
//����ʵ��
//������̳:www.openedv.com	
/*
void dis_play(int16_t num,u8 n)	
{
	if(num<0)
	{
		num=-num;
		USART_SendData(USART1,'-');
	}
	else
		USART_SendData(USART1,'+');
	//if(n)
	USART_SendData(USART1,0x30|(num/10000));	
	USART_SendData(USART1,0x30|(num%10000/1000));
	USART_SendData(USART1,0x30|(num%1000/100));
	USART_SendData(USART1,0x2e);
	USART_SendData(USART1,0x30|(num%100/10));
	USART_SendData(USART1,0x30|(num%10));
	USART_SendData(USART1,',');
}
*/
int main(void)
 {
	
//	u8 t;
//	u8 len;	
	static u8  times=0;  	
 	SystemInit();//ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart1_init(115200);//���ڳ�ʼ��Ϊ115200
	 uart2_init(115200);//���ڳ�ʼ��Ϊ115200
	while(1)
	{
		/*
		if(flag==0)
		{
		  USART_SendData(USART1,0xa5);
			USART_SendData(USART1,0x51);//��һ��ѯָ��
		}
		delay_ms(10);
		*/
		if(times==0)
		{
			times=1;//ֻ��һ��
		  USART_SendData(USART2,0xa5);
			USART_SendData(USART2,0x52);//�Զ�����16��������ָ��
		}
		
		if(flag==1)
		{	
			 USART_SendData(USART1,'Y');
			 USART_SendData(USART1,YAW);
	     USART_SendData(USART1,PITCH);
	     USART_SendData(USART1,ROLL);
			/*
			 flag=0;
			 USART_SendData(USART1,'#');
	     USART_SendData(USART1,'Y');
	     USART_SendData(USART1,'P');
	     USART_SendData(USART1,'R');
	     USART_SendData(USART1,'=');
			 dis_play(YAW,1);
			 dis_play(PITCH,0);
			 dis_play(ROLL,0);
			 USART_SendData(USART1,0X0d);
	     USART_SendData(USART1,0X0a);
			*/
		}
	}	 

 }

