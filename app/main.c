//#define Stack_Size 0x200
#include "sch.h"
#include "drv_led.h"
#include "drv_ds1302.h"
#include <stdio.h>
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
	SCH_Add_Task(LED_Task2, 600, 1100);
	SCH_Add_Task(DS1302_Test, 100, 1000);
	//SCH_Add_Task(HC575_Task, 0, 200);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}


void MQ_Insert(int msg)
{}

void Console_Task()
{
	int msg_type;
	//UART_Print(MQ_Get(msg_type));
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
	static u8 led1_flash_times = 0;
	int led1_msg;
	LED1_REVERSE();
	buf1[11]++;
	MQ_Insert(led1_msg);
	if(RT_OK == MQ_enQueue(mq,buf1)){
		printf("enqueue OK,value is %s\n",buf1);
	}
	else{
		printf("enqueue FAIL\n");
	}
//	printf("mq size is %d, context is %c!\n",MQ_getSize(mq),MQ_deQueue(mq));

}


void LED_Task2()
{
	char  **buf2;
	LED2_REVERSE();
	//printf("LED_Taks2!\n");

	if(RT_OK == MQ_deQueue(mq,buf2)){
		printf("dequeue OK,value is %s\n",*buf2);
	}
	else{
		printf("dequeue FAIL\n");
	}
	UART_Write(UART0,(uint8_t *)buf1,(u32)strlen((const char *)buf1));
	
}



