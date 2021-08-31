#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

float adcValue=0,led=0;
uint16_t button=0,sayac=0;

void gpioConfig(){
		GPIO_InitTypeDef GPIOInitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//ADC port
	 GPIOInitStructer.GPIO_Mode=GPIO_Mode_AIN;
	 GPIOInitStructer.GPIO_Pin=GPIO_Pin_6;
	
	 GPIO_Init(GPIOA,&GPIOInitStructer);
	 //PWM port
	 GPIOInitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
	 GPIOInitStructer.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3;
	 GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	 GPIO_Init(GPIOA,&GPIOInitStructer);
	 //Button port
	 GPIOInitStructer.GPIO_Mode=GPIO_Mode_IPD;
	 GPIOInitStructer.GPIO_Pin=GPIO_Pin_10;
	 GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIOInitStructer);
}
void extiConfig(){
		EXTI_InitTypeDef EXTIinitStructer;
		NVIC_InitTypeDef NVICInitStructer;
	
		EXTIinitStructer.EXTI_Line=EXTI_Line10;
	  EXTIinitStructer.EXTI_LineCmd=ENABLE;
	  EXTIinitStructer.EXTI_Mode=EXTI_Mode_Interrupt;
	  EXTIinitStructer.EXTI_Trigger=EXTI_Trigger_Rising;
	
	  EXTI_Init(&EXTIinitStructer);
	  
		NVICInitStructer.NVIC_IRQChannel=EXTI15_10_IRQn;
	  NVICInitStructer.NVIC_IRQChannelCmd=ENABLE;
	  NVICInitStructer.NVIC_IRQChannelPreemptionPriority=1;
	  NVICInitStructer.NVIC_IRQChannelSubPriority=1;
	
	 NVIC_Init(&NVICInitStructer);

}
void adcConfig(){
	 ADC_InitTypeDef ADCInitStructer;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);


	 ADCInitStructer.ADC_ContinuousConvMode=ENABLE;
	 ADCInitStructer.ADC_DataAlign=ADC_DataAlign_Right;
	 ADCInitStructer.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	 ADCInitStructer.ADC_Mode=ADC_Mode_Independent;
	 ADCInitStructer.ADC_NbrOfChannel=1;
	 ADCInitStructer.ADC_ScanConvMode=DISABLE;
	
	 ADC_Init(ADC1,&ADCInitStructer);
	 ADC_Cmd(ADC1,ENABLE);
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
void pwmConfig(float pulse){
	 TIM_OCInitTypeDef TIMOCInitStructer;
	 
	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
	 TIMOCInitStructer.TIM_Pulse=pulse;

	 
	 TIM_OC1Init(TIM2,&TIMOCInitStructer);
	 TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);	
}
//void pwm1Config(uint32_t pulseRgb){
//	 TIM_OCInitTypeDef TIMOCInitStructer;
//	 
//	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
//	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
//	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
//	 TIMOCInitStructer.TIM_Pulse=pulseRgb;

//	 
//	 TIM_OC2Init(TIM2,&TIMOCInitStructer);
//	 TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);	
//}
//void pwm2Config(uint32_t pulseRgb){
//	 TIM_OCInitTypeDef TIMOCInitStructer;
//	 
//	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
//	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
//	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
//	 TIMOCInitStructer.TIM_Pulse=pulseRgb;

//	 
//	 TIM_OC3Init(TIM2,&TIMOCInitStructer);
//	 TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);	
//}
//void pwm3Config(uint32_t pulseRgb){
//	 TIM_OCInitTypeDef TIMOCInitStructer;
//	 
//	 TIMOCInitStructer.TIM_OCMode=TIM_OCMode_PWM1;
//	 TIMOCInitStructer.TIM_OCPolarity=TIM_OCPolarity_High;
//	 TIMOCInitStructer.TIM_OutputState=TIM_OutputState_Enable;
//	 TIMOCInitStructer.TIM_Pulse=pulseRgb;

//	 
//	 TIM_OC4Init(TIM2,&TIMOCInitStructer);
//	 TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);	
//}
uint16_t adcRead(){
   ADC_RegularChannelConfig(ADC1,ADC_Channel_6,1,ADC_SampleTime_55Cycles5);
	 ADC_SoftwareStartConvCmd(ADC1,ENABLE);	
	
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
		return ADC_GetConversionValue(ADC1);
}
void delay(uint32_t time){

	while(time--);
}
void EXTI15_10_IRQHandler(){

		if(EXTI_GetITStatus(EXTI_Line10)!=RESET){
			sayac++;
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
}
int main(){
	gpioConfig();
	adcConfig();
	timConfig();
  extiConfig();
	
	while(1){
			adcValue=adcRead();
			led=(adcValue*2399/4095);
			pwmConfig(led);
//	  	button=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
//			if(sayac==1){
//				pwm1Config(2399);pwm2Config(0);pwm3Config(0);
//			}
//			else if(sayac==2){
//				pwm1Config(0);pwm2Config(2399);pwm3Config(0);
//			}
//			else if(sayac==3){
//				pwm1Config(0);pwm2Config(0);pwm3Config(2399);
//			}
//			else{
//			sayac=0;
//			}
			
	}
}
