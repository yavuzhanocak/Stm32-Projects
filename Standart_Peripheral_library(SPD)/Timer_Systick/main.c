#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
uint16_t counter=0;
void gpioConfig(){
		GPIO_InitTypeDef GPIOinitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
		GPIOinitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIOinitStructer.GPIO_Pin=GPIO_Pin_9;
		GPIOinitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOC,&GPIOinitStructer);

}
void SysTick_Handler(){
	if(counter>0)counter--;
}
void delay_ms(uint32_t time){
	counter=time;
	while(counter);

}
int main(){
		gpioConfig();
		SystemCoreClockUpdate();
		SysTick_Config(SystemCoreClock/1000);//1 ms 
		//SysTick_Config(SystemCoreClock/1000000);//1 us 

	while(1){
			GPIO_SetBits(GPIOC,GPIO_Pin_9);
			delay_ms(1000);
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			delay_ms(1000);
			
	}
}
