//#define Stack_Size 0x200
#include "nuc123.h"
#include "sch.h"
#include "drv_74hc595.h"


uint8_t g_led_flag = 0;
uint8_t g_led2_flag = 0;
//uint8_t g_tmp = 0xaa;

void LED_Task1()
{
	if(1 == g_led_flag )
	{
			g_led_flag = 0;
			PA12 = ~PA12;
	}
	else g_led_flag = 1;

	
}

void LED_Task2()
{
	if(1 == g_led2_flag )
	{
			g_led2_flag = 0;
			PA13 = ~PA13;
	}
	else g_led2_flag = 1;

	
}



void HC575_Task()
{
	static uint16_t tmp =0x0f;
	HC575_Output_Data(tmp++);
}





void SYS_Init()
{
	SYS->GPA_MFP &= ~(SYS_GPA_MFP_PA12_Msk |SYS_GPA_MFP_PA12_Msk );
	SYS->GPA_MFP |= (SYS_GPA_MFP_PA12_GPIO |SYS_GPA_MFP_PA12_GPIO);
	GPIO_SetMode(PA,BIT12|BIT13,GPIO_PMD_OUTPUT);
	PA12 = 0;
	PA13 = 0;
	HC575_Init();
}

int main(void)
{
	SYS_Init();
	SCH_Init_T0();
	SCH_Add_Task(LED_Task1, 0, 200);
	SCH_Add_Task(LED_Task2, 0, 500);
	SCH_Add_Task(HC575_Task, 0, 200);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}

