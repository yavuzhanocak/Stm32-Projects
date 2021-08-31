#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
uint16_t adcValue=0;
float voltage=0;
float angle=0;
float ldr=0;
void gpioconfig(){
		GPIO_InitTypeDef GPIOInitStructer;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		GPIOInitStructer.GPIO_Mode=GPIO_Mode_AIN;
		GPIOInitStructer.GPIO_Pin=GPIO_Pin_3;
	
		GPIO_Init(GPIOA,&GPIOInitStructer);
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
		ADC_Cmd(ADC1,ENABLE );
}
uint16_t adcRead(){
	
		ADC_RegularChannelConfig(ADC1,ADC_Channel_3,1,ADC_SampleTime_55Cycles5);
	  ADC_SoftwareStartConvCmd(ADC1,ENABLE);

		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
		return ADC_GetConversionValue(ADC1);
}
float map(float adcValue,float adcmax,float adcmin,float max,float min){
			return adcValue*((max-min)/(adcmax-adcmin));
}

int main(){
	gpioconfig();
	adcConfig();
	while(1){
		adcValue=adcRead();
		//voltage=adcValue*(4.35)/(4095);
		//voltage=map(adcValue,4095,0,2.48,0);
		//angle=map(adcValue,4095,0,180,0);
		ldr=map(adcValue,4095,0,2.48,0);
	}
}
