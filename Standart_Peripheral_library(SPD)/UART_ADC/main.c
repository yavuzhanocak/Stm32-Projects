#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC 
#include <stdio.h>
uint16_t adcvalue=0;
char senddata[20];
char test[20]="HELLO WORC\r\n";
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIOInitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_9;
	GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOInitStructer);
	
	GPIOInitStructer.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_1;
	
	
	GPIO_Init(GPIOA,&GPIOInitStructer);

}
void uartConfig(){
	USART_InitTypeDef USARTInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	USARTInitStructer.USART_BaudRate=9600;
	USARTInitStructer.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USARTInitStructer.USART_Mode=USART_Mode_Tx;
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

void adcConfig(){
	ADC_InitTypeDef ADCInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADCInitStructer.ADC_ContinuousConvMode=ENABLE;
	ADCInitStructer.ADC_DataAlign=ADC_DataAlign_Right;
	ADCInitStructer.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADCInitStructer.ADC_Mode=ADC_Mode_Independent;
	ADCInitStructer.ADC_NbrOfChannel=1;
	ADCInitStructer.ADC_ScanConvMode=DISABLE ;

	ADC_Init(ADC1,&ADCInitStructer);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t adcRead(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET );
		return ADC_GetConversionValue(ADC1);
	
	
}
void delay(uint32_t time){

	while(time--);
}
int main(){
	gpioConfig();
	uartConfig();
	adcConfig();
	while(1){
		adcvalue=adcRead();
		sprintf(senddata,"%d\r\n",adcvalue);
		uartTransmit(senddata);
		delay(3600000);
	}
}
