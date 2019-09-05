//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"
#include "drv_ds1302.h"
#include "drv_mcp7425.h"
#include "drv_adc.h"
#include "drv_nuc123.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mq.h"
#include "time.h"

void SYS_Init(void);
void ADC_Task(void);
void NUC123_GPIO_Task(void);
void RunTime_Task(void);
extern void DS1302_Test(void);
extern void MCP7425_Init(void);


MQ *mq;
RunTime sys_run_time;

char  buf1[20] = "Hello World0";
int main(void)
{

	SYS_Init();
	SCH_Add_Task(RunTime_Task, 0, 1000);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}






void UART0_Init()
{
	
	    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));
	
	    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);
	
	SYS->GPC_MFP &= ~(SYS_GPC_MFP_PC4_Msk | SYS_GPC_MFP_PC5_Msk);
	SYS->GPC_MFP |= (SYS_GPC_MFP_PC4_UART0_RXD | SYS_GPC_MFP_PC5_UART0_TXD);

	SYS->ALT_MFP &= ~(SYS_ALT_MFP_PC4_Msk | SYS_ALT_MFP_PC5_Msk);
	SYS->ALT_MFP |= (SYS_ALT_MFP_PC4_UART0_RXD | SYS_ALT_MFP_PC5_UART0_TXD);
	
	
	UART_Open(UART0,115200);


		
}

void SYS_Init()
{
		SCH_Init_T0();
		DRV_LED_Init();
		UART0_Init();
		//ADC_Init();
		//NUC123_Init();
		MCP7425_Init();
		RunTime_Reset(&sys_run_time);
}


//char str[]={"Hello World!\n"};

void RunTime_Task()
{
	RunTime_Click(&sys_run_time);
	printf("the sys_run_time is %d:%d:%d:%d\n",sys_run_time.byte[3],sys_run_time.byte[2],sys_run_time.byte[1],sys_run_time.byte[0]);
}








