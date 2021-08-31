#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
uint16_t segementnum[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0X07,0X7F,0X6F};
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOInitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOInitStructer);

}

int main(){
	gpioConfig();
	while(1){
	GPIOA->ODR=segementnum[9];
	}
}