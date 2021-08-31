#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
int i=0;
void gpioConfig(){
		GPIO_InitTypeDef GPIOInitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		GPIOInitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIOInitStructer.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2;
		GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA,&GPIOInitStructer);

}
void timConfig(){
		TIM_TimeBaseInitTypeDef TIMInitStructer;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
		TIMInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
		TIMInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
		TIMInitStructer.TIM_Period=2399;
		TIMInitStructer.TIM_Prescaler=10;
		TIMInitStructer.TIM_RepetitionCounter=0;
	
		TIM_TimeBaseInit(TIM2,&TIMInitStructer);
		TIM_Cmd(TIM2,ENABLE);

}
void pwm0Config(uint16_t timpulse){
	 TIM_OCInitTypeDef TIMOCInitStructer;
		
	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
	 TIMOCInitStructer.TIM_Pulse=timpulse;
	 
	 TIM_OC1Init(TIM2,&TIMOCInitStructer);
	 TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void pwm1Config(uint16_t timpulse){
	 TIM_OCInitTypeDef TIMOCInitStructer;
		
	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
	 TIMOCInitStructer.TIM_Pulse=timpulse;
	 
	 TIM_OC2Init(TIM2,&TIMOCInitStructer);
	 TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void pwm2Config(uint16_t timpulse){
	 TIM_OCInitTypeDef TIMOCInitStructer;
		
	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
	 TIMOCInitStructer.TIM_Pulse=timpulse;
	 
	 TIM_OC3Init(TIM2,&TIMOCInitStructer);
	 TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void delay(uint16_t time){
		while(time--);
}
int main(){
  gpioConfig();
	timConfig();
	while(1){
				for(i=0;i<2399;i++){
						pwm0Config(i);
						delay(180);
				}
				for( i=0;i<2399;i++){
						pwm1Config(i);
						delay(180);
				}
				for( i=0;i<2399;i++){
						pwm2Config(i);
						delay(180);
				}
	}
}