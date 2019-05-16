
#include "drv_74hc595.h"
#include "drv_common.h"



void HC575_Init(void)
{
	SYS->GPC_MFP &= ~(SYS_GPC_MFP_PC3_Msk |SYS_GPC_MFP_PC2_Msk |SYS_GPC_MFP_PC1_Msk |SYS_GPC_MFP_PC0_Msk );
	SYS->GPC_MFP |= (SYS_GPC_MFP_PC3_GPIO |SYS_GPC_MFP_PC2_GPIO |SYS_GPC_MFP_PC1_GPIO |SYS_GPC_MFP_PC0_GPIO);
	GPIO_SetMode(PC,BIT3 |BIT2 |BIT1 |BIT0,GPIO_PMD_OUTPUT);
	
	
	PIN_HC575_RST_N = 0;
	PIN_HC575_LCK = 0;
	PIN_HC575_SCK = 0;
	PIN_HC575_SI = 0;
#ifdef PIN_HC575_OE_N
	PIN_HC575_OE_N = 1;
#endif
	

}

//void 

void HC575_SetSR_Data(uint16_t sdata_in)
{
	uint16_t  i;
	PIN_HC575_RST_N = 1;
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

void HC575_Output_Data(uint16_t sdata)
{

	HC575_SetSR_Data(sdata);
	HC575_SetLR();
#ifdef PIN_HC575_OE_N
	PIN_HC575_OE_N = 0;
#endif
}
