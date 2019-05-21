//#define Stack_Size 0x200
#include "drv_led.h"











void DRV_LED_Init()
{
	// LED1 PA12  LED2 PA13
	SYS->GPA_MFP &= ~(SYS_GPA_MFP_PA12_Msk |SYS_GPA_MFP_PA12_Msk );
	SYS->GPA_MFP |= (SYS_GPA_MFP_PA12_GPIO |SYS_GPA_MFP_PA12_GPIO);
	GPIO_SetMode(PA,BIT12|BIT13,GPIO_PMD_OUTPUT);
	PA12 = 0;
	PA13 = 0;
}



