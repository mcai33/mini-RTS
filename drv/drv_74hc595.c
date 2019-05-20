#include "drv_74hc595.h"

void HC575_Init(void)
{

	HC575_INIT;

#ifdef PIN_HC575_RST_N
	PIN_HC575_RST_N = 0;
#endif
	PIN_HC575_LCK = 0;
	PIN_HC575_SCK = 0;
	PIN_HC575_SI = 0;
#ifdef PIN_HC575_OE_N
	PIN_HC575_OE_N = 1;
#endif
}


void HC575_SetSR_Data(u16 sdata_in)
{
	u16  i;
#ifdef PIN_HC575_RST_N
	PIN_HC575_RST_N = 1;
#endif
	sw_delay_1us();
	for(i = 0;i < 8; i++)
	{
		PIN_HC575_SCK = 0;
		sw_delay_1us();
		PIN_HC575_SI = ((sdata_in >> i) & 0x01 );
		sw_delay_1us();
		PIN_HC575_SCK = 1;
	}	
	sw_delay_1us();
}


void HC575_SetLR(void)
{
	PIN_HC575_LCK = 0;
	sw_delay_1us();
	PIN_HC575_LCK = 1;
	sw_delay_1us();
}

void HC575_Output_Data(u16 sdata)
{

	HC575_SetSR_Data(sdata);
	HC575_SetLR();
#ifdef PIN_HC575_OE_N
	PIN_HC575_OE_N = 0;
#endif
}
