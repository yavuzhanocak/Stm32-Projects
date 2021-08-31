#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
uint32_t counter1=0;
void gipoconfig(){
	GPIO_InitTypeDef GPIOinitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIOinitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIOinitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIOinitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOinitStructure);
	
	GPIOinitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOinitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIOinitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIOinitStructure);
}
void exticonfig(){

	EXTI_InitTypeDef EXTIInitStructer;
	NVIC_InitTypeDef NVICInitStructer;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTIInitStructer.EXTI_Line=EXTI_Line10;
	EXTIInitStructer.EXTI_LineCmd=ENABLE;
	EXTIInitStructer.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTIInitStructer.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTIInitStructer);
	
	NVICInitStructer.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVICInitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVICInitStructer.NVIC_IRQChannelPreemptionPriority=1;
	NVICInitStructer.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVICInitStructer);



}
void delay(uint32_t time){
	while(time--);
}
void EXTI15_10_IRQHandler(){
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET){
		counter1++;
	
	}
	EXTI_ClearITPendingBit(EXTI_Line10);
}
int main(){
		gipoconfig();
	  exticonfig();
	while(1){
	
	}
}