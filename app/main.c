//#define Stack_Size 0x200
#include "sch.h"
//#include "drv_led.h"
#include "drv_74hc595.h"


void SYS_Init()
{
		SCH_Init_T0();
		//DRV_LED_Init();
		HC595_Init();
		HC595_Output_Data(0x0f);
}






int main(void)
{
	SYS_Init();
	//SCH_Add_Task(HC575_Task, 0, 200);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}

