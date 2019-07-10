//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"
#include <stdio.h>

void SYS_Init(void);
void LED_Task1(void);
void LED_Task2(void);

    enum DEVICE_ID_E {
        DEVICE_ID_1 = 0,
        DEVICE_ID_2,
        DEVICE_ID_3,
        DEVICE_ID_4,
        DEVICE_ID_5,
        DEVICE_ID_6,
        DEVICE_ID_MALLOC = 0xFC,
        DEVICE_ID_IN_USING = 0xFD,
        DEVICE_ID_UNKNOWN = 0xFE,
        DEVICE_ID_OVERFLOW = 0xFF
    };

int main(void)
{
	SYS_Init();
	SCH_Add_Task(LED_Task1, 0, 500);
	SCH_Add_Task(LED_Task2, 0, 200);
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
	printf("LED_Taks1!\n");

}


void LED_Task2()
{
	LED2_REVERSE();
	printf("LED_Taks2!\n");
}



