/*******************************************************************************
*                 
*                 		       普中科技
--------------------------------------------------------------------------------
* 实 验 名		 : ADC转换实验
* 实验说明       : 通过printf打印AD检测数据 ，调节AD模块旁边的电位器 在串口助手上即可输出电压，
					见文件内截图
* 连接方式       : 
* 注    意		 : 	所用函数在头文件.c文件内
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
	float ADC_Value[3];//用来保存经过转换得到的电压值
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
				//	printf("Inside：。%f\r\n",ADC_ConvertedValue[j][i]);
				}
				ADC_Value[i]=(float)sum/(10*4096)*3.3;//求平均值并转换成电压值
		
			}
				 
			printf("The current AD value =%f\r\n",ADC_Value[0]);
			printf("The current AD value =%f\r\n",ADC_Value[1]);
			printf("The current AD value =%f\r\n",ADC_Value[2]);
			delay_ms(100);
    }
  return 0;

}



