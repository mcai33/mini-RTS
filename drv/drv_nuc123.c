#include "nuc123.h"
#include "drv_nuc123.h"

void NUC123_Init(void)
{
	//set PB7 GPIO push pull
	SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB7_Msk );
	SYS->GPB_MFP |= (SYS_GPB_MFP_PB7_GPIO );

	SYS->ALT_MFP &= ~(SYS_ALT_MFP_PB7_Msk );
	SYS->ALT_MFP |= (SYS_ALT_MFP_PB7_GPIO );
	
	GPIO_SetMode(PB,BIT7,GPIO_PMD_OUTPUT);

}

