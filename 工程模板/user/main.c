/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : ADCת��ʵ��
* ʵ��˵��       : ͨ��printf��ӡAD������� ������ADģ���Աߵĵ�λ�� �ڴ��������ϼ��������ѹ��
					���ļ��ڽ�ͼ
* ���ӷ�ʽ       : 
* ע    ��		 : 	���ú�����ͷ�ļ�.c�ļ���
*******************************************************************************/


#include "public.h"
#include "printf.h"
#include "adc.h"
#include "systick.h"

/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

extern uint16_t ADC_ConvertedValue[10][3];
float ADC_ConvertedValueLocal;
void Delay(__IO uint32_t nCount)
{
   for(;nCount !=0;nCount--);
}

int main()
{	
	int sum;
	u8 i,j;
	float ADC_Value[3];//�������澭��ת���õ��ĵ�ѹֵ
	printf_init();	
  adc_init();
  printf("******This is a ADC test******\n");
	
	
  while(1)
    {
      //  ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
       
	//	printf("The current AD value =%f V\n",ADC_ConvertedValueLocal);
		
			
			for(i=0;i<3;i++)
			{
				sum=0;
				
				for(j=0;j<10;j++)
				{
					sum +=ADC_ConvertedValue[j][i];
				//	printf("Inside����%f\r\n",ADC_ConvertedValue[j][i]);
				}
				ADC_Value[i]=(float)sum/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
		
			}
				 
			printf("The current AD value =%f\r\n",ADC_Value[0]);
			printf("The current AD value =%f\r\n",ADC_Value[1]);
			printf("The current AD value =%f\r\n",ADC_Value[2]);
			delay_ms(100);
    }
  return 0;

}



