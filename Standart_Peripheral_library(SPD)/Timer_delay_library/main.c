#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "delay.h"
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIOInitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_9;
	GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIOInitStructer);
}
int main(){
	 gpioConfig();
	 DelayInit();
	while(1){
			GPIO_SetBits(GPIOC,GPIO_Pin_9);
			delay_ms(1000);
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			delay_ms(1000);
	}
}
