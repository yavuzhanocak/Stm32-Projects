#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOInitStructer.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStructer.GPIO_Pin=GPIO_Pin_4;
	GPIOInitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOInitStructer);

}
void dacConfig(){
	DAC_InitTypeDef DACInitStructer;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);

 DACInitStructer.DAC_LFSRUnmask_TriangleAmplitude=DISABLE;
	DACInitStructer.DAC_OutputBuffer=ENABLE;
	DACInitStructer.DAC_Trigger=DAC_Trigger_None;
	DACInitStructer.DAC_WaveGeneration=DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1,&DACInitStructer);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}
void delay(uint32_t time){

	while(time--);
}

int main(){
 gpioConfig();
 dacConfig();
	while(1){
			for(int i=0;i<4095;i++){
					DAC_SetChannel1Data(DAC_Align_12b_R,i);
					delay(3600);
			}
				for(int i=4095;i>0;i--){
					DAC_SetChannel1Data(DAC_Align_12b_R,i);
					delay(3600);
			}
	}
}