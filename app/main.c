//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"
#include "drv_ds1302.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mq.h"

void SYS_Init(void);
void LED_Task1(void);
void LED_Task2(void);
extern void DS1302_Test(void);

MQ *mq;

char  buf1[20] = "Hello World0";

int main(void)
{
	mq = MQ_Create();
	if(RT_OK == MQ_enQueue(mq,buf1)){
		printf("enqueue OK,value is %s\n",buf1);
	}
	else{
		printf("enqueue FAIL\n");
	}
	SYS_Init();
	SCH_Add_Task(LED_Task1, 0, 1000);
	SCH_Add_Task(LED_Task2, 0, 1100);
	//SCH_Add_Task(DS1302_Test, 100, 1000);
	//SCH_Add_Task(HC575_Task, 0, 200);
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
		
}


//char str[]={"Hello World!\n"};

void LED_Task1()
{
	LED1_REVERSE();
	buf1[11]++;
	if(RT_OK == MQ_enQueue(mq,buf1)){
		printf("TASK1 enqueue OK,value is %s\n",buf1);
	}
	else{
		printf("enqueue FAIL\n");
	}
//	printf("mq size is %d, context is %c!\n",MQ_getSize(mq),MQ_deQueue(mq));

}


void LED_Task2()
{
	char  *buf2 = "abcde";
	LED2_REVERSE();
	//printf("LED_Taks2!\n");
	buf2 = MQ_deQueue(mq);
	printf("      TASK2 deQueue OK,value is %s\n",buf2);
	free(buf2);
	//free()
	//UART_Write(UART0,(uint8_t *)buf1,(u32)strlen((const char *)buf1));
	
}



