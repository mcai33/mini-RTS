//#define Stack_Size 0x200
#include <stdio.h>
#include "sch.h"
#include "drv_led.h"
#include "drv_74hc595.h"
#include "hid_transfer.h"
#include "drv_nuc123.h"
#include "uart.h"

void LED_Task1()
{
	LED1_REVERSE();
	printf("LED1 Reverse \n");

}

void LED_Task2()
{
	LED2_REVERSE();
	printf("LED2 Reverse \n");
}


const char a[]="abcdefg";
uint8_t b[]="1234567890";

void HID_Task()
{
//	HID_CmdTest(0x00);
	//void HID_SetInReport(void);
	//HID_GetOutReport(b, 5);
	HID_TEST();
	printf("HID Task \n");
}



void SYS_Init()
{
	  printf("\n %s System Start: \n",a);
		MCU_Init();
		SCH_Init_T0();
		DRV_LED_Init();
		HC595_Init();
		HC595_Output_Data(0xbf);
}






int main(void)
{
	SYS_Init();
	//SCH_Add_Task(LED_Task1, 0, 200);
	//SCH_Add_Task(LED_Task2, 0, 500);
	SCH_Add_Task(HID_Task, 0, 500);	
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}

