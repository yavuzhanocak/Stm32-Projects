#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(){
		GPIO_InitTypeDef GPIOInitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE );

	  GPIOInitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIOInitStructer.GPIO_Pin=GPIO_Pin_0;
	  GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIOInitStructer);
}
void timConfig(){
		TIM_TimeBaseInitTypeDef TIMInitStructer;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	  TIMInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIMInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
	  TIMInitStructer.TIM_Period=4799;
	  TIMInitStructer.TIM_Prescaler=100;
	  TIMInitStructer.TIM_RepetitionCounter=0;
	  
	  TIM_TimeBaseInit(TIM2,&TIMInitStructer);
		TIM_Cmd(TIM2,ENABLE);
}
void pwmConfig(uint16_t pulse){
		TIM_OCInitTypeDef TIMPWMInitStructer;
		
    TIMPWMInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
		TIMPWMInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
		TIMPWMInitStructer.TIM_OutputState=TIM_OutputState_Enable;
		TIMPWMInitStructer.TIM_Pulse=pulse;
		
		TIM_OC1Init (TIM2,&TIMPWMInitStructer);
		TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
void delay(uint32_t time){
		while(time--);

}

int main(){
  gpioConfig();
	 timConfig();
	while(1){
			pwmConfig(359);
			delay(7200000);
		  pwmConfig(480);
			delay(720000);
			pwmConfig(240);
			delay(7200000);
	}
}
