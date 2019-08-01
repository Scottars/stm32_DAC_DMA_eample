#include "adc.h"
#include "stm32f10x_dma.h"
/*******************************************************************************
* �� �� ��         : adc_init
* ��������		   : IO�˿�ʱ�ӳ�ʼ������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
volatile uint16_t ADC_ConvertedValue[10][3];
void adc_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
		DMA_InitTypeDef DMA_InitStructure;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC1,ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  ???14M ????ADC????ADCCLK??

  
		DMA_DeInit(DMA1_Channel1);    //��ͨ��һ�Ĵ�����ΪĬ��ֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);//�ò������Զ���DMA�������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;//�ò������Զ���DMA�ڴ����ַ(ת���������ĵ�ַ)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�ò����涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ���˴�����Ϊ��Դ
    DMA_InitStructure.DMA_BufferSize = 3*10;//����ָ��DMAͨ����DMA����Ĵ�С,��λΪ���ݵ�λ������Ҳ����ADCConvertedValue�Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�趨�����ַ�Ĵ����������,�˴���Ϊ���� Disable
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�����趨�ڴ��ַ�Ĵ����������,�˴���Ϊ������Enable
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ��ӵ�и����ȼ� �ֱ�4���ȼ� �͡��С��ߡ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//ʹ��DMAͨ�����ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

    DMA_Cmd(DMA1_Channel1, ENABLE);//����DMAͨ��һ

	
	
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2;//ADC
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN; //???????
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

		
	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 3;
    ADC_Init(ADC1, &ADC_InitStructure);

    //???????ADC??????????????????????????????????
   
		//RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz  ���������Ѿ����ж�����
		//ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_239Cycles5);//ͨ��һת��������浽ADCConvertedValue[0~10][0]
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_239Cycles5);//ͨ����ת��������浽ADCConvertedValue[0~10][1]
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,3,ADC_SampleTime_239Cycles5);//ͨ����ת��������浽ADCConvertedValue[0~10][2]



		ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);//?????????ADC??��??????
    while(ADC_GetResetCalibrationStatus(ADC1));//???ADC????��??????????

    ADC_StartCalibration(ADC1);//??????ADC??��???
    while(ADC_GetCalibrationStatus(ADC1));//??????ADC??��?????

ADC_SoftwareStartConvCmd(ADC1, ENABLE);//??????????????ADC???????????????


}
