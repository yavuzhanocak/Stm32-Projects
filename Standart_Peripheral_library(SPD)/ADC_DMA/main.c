#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOInitStructer.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_0;
	
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
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
uint32_t adcRead[];
void dmaConfig(){
	DMA_InitTypeDef DAMInitstructer;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_DeInit(DMA1_Channel1);
	
	DAMInitstructer.DMA_BufferSize=1;
	DAMInitstructer.DMA_DIR=DMA_DIR_PeripheralSRC;
	DAMInitstructer.DMA_M2M=DMA_M2M_Disable;
	DAMInitstructer.DMA_MemoryBaseAddr=(uint32_t) adcRead;
	DAMInitstructer.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DAMInitstructer.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DAMInitstructer.DMA_Mode=DMA_Mode_Circular;
	DAMInitstructer.DMA_PeripheralBaseAddr=(uint32_t) & ADC1->DR;
	DAMInitstructer.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DAMInitstructer.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DAMInitstructer.DMA_Priority=DMA_Priority_High;
	
	DMA_Init(DMA1_Channel1,&DAMInitstructer);
	DMA_Cmd(DMA1_Channel1,ENABLE);


}
int main(){
	gpioConfig();
	adcConfig();
	dmaConfig();
	while(1){
	
	}
}