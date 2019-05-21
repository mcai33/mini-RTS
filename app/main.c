//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"


void SYS_Init()
{
		SCH_Init_T0();
		DRV_LED_Init();
}


void LED_Task1()
{
	LED1_REVERSE();
}

void LED_Task2()
{
	LED2_REVERSE();
}

int main(void)
{
	SYS_Init();
	SCH_Add_Task(LED_Task1, 0, 200);
	SCH_Add_Task(LED_Task2, 0, 500);
	//SCH_Add_Task(HC575_Task, 0, 200);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}

