#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

char test[20]="HELLO WORD\r\n";
uint16_t data=0;
void gpioCoinfig(){
	  GPIO_InitTypeDef GPIOInitStructer;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		//TX
    GPIOInitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIOInitStructer.GPIO_Pin=GPIO_Pin_9;
		GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIOInitStructer);
		//RX
	  GPIOInitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIOInitStructer.GPIO_Pin=GPIO_Pin_10;
		
		GPIO_Init(GPIOA,&GPIOInitStructer);
		//LED
		GPIOInitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIOInitStructer.GPIO_Pin=GPIO_Pin_9;
		GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOC,&GPIOInitStructer);
}
void usartConfig(){
		USART_InitTypeDef USARTInitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	  USARTInitStructer.USART_BaudRate=9600;
		USARTInitStructer.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	  USARTInitStructer.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
		USARTInitStructer.USART_Parity=USART_Parity_No;
	  USARTInitStructer.USART_StopBits=USART_StopBits_1;
	  USARTInitStructer.USART_WordLength=USART_WordLength_8b;
	
		USART_Init(USART1,&USARTInitStructer);
		USART_Cmd(USART1,ENABLE);

}
void uartTransmit(char *string){
   while(*string){
      while(!(USART1->SR & 0x00000040));
      USART_SendData(USART1,*string);
      *string++;

   }
}
int main(){
	gpioCoinfig();
	usartConfig();
	while(1){
			//uartTransmit(test);
			data=USART_ReceiveData(USART1);
		
					if(data=='1'){
						GPIO_SetBits(GPIOC,GPIO_Pin_9 );

					}
					else if(data=='0'){
						GPIO_ResetBits(GPIOC,GPIO_Pin_9);
					}
	}
}
