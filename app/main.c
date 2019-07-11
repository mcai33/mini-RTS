//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"
#include "drv_ds1302.h"
#include <stdio.h>

void SYS_Init(void);
void LED_Task1(void);
void LED_Task2(void);
extern void DS1302_Test(void);

int main(void)
{
	SYS_Init();
	SCH_Add_Task(LED_Task1, 0, 500);
	SCH_Add_Task(LED_Task2, 0, 200);
	SCH_Add_Task(DS1302_Test, 100, 1000);
	//SCH_Add_Task(HC575_Task, 0, 200);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}





void SYS_Init()
{
		SCH_Init_T0();
		DRV_LED_Init();
}


//char str[]={"Hello World!\n"};

void LED_Task1()
{
	LED1_REVERSE();
	//printf(%d,DEVICE_ID_E.DEVICE_ID_1);
	//printf("LED_Taks1!\n");

}


void LED_Task2()
{
	LED2_REVERSE();
	//printf("LED_Taks2!\n");
}



