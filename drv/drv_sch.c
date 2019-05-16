
#include "drv_sch.h"


//extern sTask SCH_tasks_G[SCH_MAX_TASKS];
//extern tByte Error_code_G;


//typedef void (*fn_timer_sch_callback)(void); 
//void *g_timer_cb = NULL;  

extern void SCH_Tick_Procced(void);

void SCH_Init_T0(void)
{
	CLK_EnableModuleClock(TMR0_MODULE);
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HXT, 0);
	NVIC_EnableIRQ(TMR0_IRQn);
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000); //set 1000Hz - 1ms -one tick
	TIMER_EnableInt(TIMER0);
}

void SCH_Start(void)
{
	TIMER_Start(TIMER0);
}


void TMR0_IRQHandler(void)
{

	if(TIMER_GetIntFlag(TIMER0) == 1)
	{
	    TIMER_ClearIntFlag(TIMER0);
	}

	SCH_Tick_Procced();

}
