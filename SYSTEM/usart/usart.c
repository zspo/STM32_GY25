#include "sys.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.3
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	  


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 

/*
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
*/
//?????
int USART_PRINTF_FLAG = 2;//????2

//??fputc
int fputc(int ch, FILE *f)
{
    if (USART_PRINTF_FLAG == 2)
    {
        while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
        USART_SendData(USART2,(uint8_t)ch);
    }
    else
    {
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
        USART_SendData(USART1,(uint8_t)ch);
    }

    return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
u8 USART_RX_BUF[64];     //���ջ���,���64���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���
/*
void uart_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
  USART_DeInit(USART1);
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
   
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
    
}
*/
/*******************************************************************************  
* ? ? ?         : uart_init  
* ????         : IO?????1,???????    A9,A10    
* ?    ?         : ?  
* ?    ?         : ?  
*******************************************************************************/    
void uart1_init(u32 bound)    
{    
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;        

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //USART1 TX;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //??????;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure); //??A;
    
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //USART1 RX;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //????;
GPIO_Init(GPIOA, &GPIO_InitStructure); //??A;

USART_InitStructure.USART_BaudRate = bound; //???;
USART_InitStructure.USART_WordLength = USART_WordLength_8b; //???8?;
USART_InitStructure.USART_StopBits = USART_StopBits_1; //???1?;
USART_InitStructure.USART_Parity = USART_Parity_No ; //????;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//?????;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//????;
USART_Init(USART1, &USART_InitStructure);//??????;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //?????,4??????,4??????;

NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //???;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //?????;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //?????;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
USART_Cmd(USART1, ENABLE); //????; 
}    

/*******************************************************************************  
* ? ? ?         : uart2_init  
* ????         : IO?????2,???????     A2,A3   
* ?    ?         : ?  
* ?    ?         : ?  
*******************************************************************************/    
void uart2_init(u32 bound)    
{    
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;        

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //USART2 TX;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //??????;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure); //??A;
    
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //USART2 RX;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //????;
GPIO_Init(GPIOA, &GPIO_InitStructure); //??A;

USART_InitStructure.USART_BaudRate = bound; //???;
USART_InitStructure.USART_WordLength = USART_WordLength_8b; //???8?;
USART_InitStructure.USART_StopBits = USART_StopBits_1; //???1?;
USART_InitStructure.USART_Parity = USART_Parity_No ; //????;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//?????;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//????;
USART_Init(USART2, &USART_InitStructure);//??????;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //?????,4??????,4??????;

NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //???;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //?????;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
USART_Cmd(USART2, ENABLE); //????;  
} 


void USART1_IRQHandler(void)
{
    USART_PRINTF_FLAG = 1;
    //your coding here...
	  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//?????USART??????  
    {    
  			USART_SendData(USART1,'Y');
			 USART_SendData(USART1,YAW);
	     USART_SendData(USART1,PITCH);
	     USART_SendData(USART1,ROLL);
    } 
}


int16_t YAW=0,PITCH=0,ROLL=0;
uint8_t flag=0;
void USART2_IRQHandler(void)                	//����2�жϷ������
	{
	static uint8_t k=0,rebuf[8]={0};
	USART_PRINTF_FLAG = 2;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		{
		 rebuf[k++] =USART_ReceiveData(USART2);	//��ȡ���յ�������
		 if(!(rebuf[0]==0xaa))//���֡ͷ�����建��
		 {
			k=0;
			rebuf[0]=0;
		 }
		 if(k==8)//���ݽ������
		 {
			if(rebuf[7]==0x55)//�ж�֡β����ȷ�������̬��
			{
			 YAW=(rebuf[1]<<8|rebuf[2]);//YAW��PITCH,ROLLΪ��ʵֵ��100��
			 PITCH=(rebuf[3]<<8|rebuf[4]);
			 ROLL=(rebuf[5]<<8|rebuf[6]);
				flag=1;
			}
			k=0;//�建��
		 }
			 
		
    } 
}

