#include "drv_74hc595.h"

void HC595_Init(void)
{

	HC595_INIT;

#ifdef PIN_HC595_RST_N
	PIN_HC595_RST_N = 0;
#endif
	PIN_HC595_LCK = 0;
	PIN_HC595_SCK = 0;
	PIN_HC595_SI = 0;
#ifdef PIN_HC595_OE_N
	PIN_HC595_OE_N = 1;
#endif
}


void HC595_SetSR_Data(u16 sdata_in)
{
	u16  i;
#ifdef PIN_HC595_RST_N
	PIN_HC595_RST_N = 1;
#endif
	sw_delay_1us();
	for(i = 0;i < 8; i++)
	{
		PIN_HC595_SCK = 0;
		sw_delay_1us();
		//PIN_HC595_SI = ((sdata_in >> i) & 0x01 );
		if( (sdata_in << i) & 0x80) PIN_HC595_SI = 1;
		else PIN_HC595_SI = 0;
		sw_delay_1us();
		PIN_HC595_SCK = 1;
		sw_delay_1us();
	}	
	sw_delay_1us();
}


void HC595_SetLR(void)
{
	PIN_HC595_LCK = 0;
	sw_delay_1us();
	PIN_HC595_LCK = 1;
	sw_delay_1us();
}

void HC595_Output_Data(u16 sdata)
{

	HC595_SetSR_Data(sdata);
	HC595_SetLR();
#ifdef PIN_HC595_OE_N
	PIN_HC595_OE_N = 0;
#endif
}
