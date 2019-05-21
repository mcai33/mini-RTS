#ifndef __DRV_74HC595__H
#define __DRV_74HC595__H

#include "nuc123.h"
#include "type.h"
#include "drv_common.h"


//PINs are necessary
#define PIN_HC595_SI PC3
#define PIN_HC595_LCK PC0
#define PIN_HC595_SCK PC1
				
//PINs are optional
//#define PIN_HC595_RST_N PC0
//#define PIN_HC595_OE_N PC4


#define HC595_INIT  {\
					SYS->GPC_MFP &= ~(SYS_GPC_MFP_PC3_Msk  |SYS_GPC_MFP_PC1_Msk |SYS_GPC_MFP_PC0_Msk );\
					SYS->GPC_MFP |= (SYS_GPC_MFP_PC3_GPIO  |SYS_GPC_MFP_PC1_GPIO |SYS_GPC_MFP_PC0_GPIO);\
					GPIO_SetMode(PC,BIT3 |BIT1 |BIT0,GPIO_PMD_OUTPUT);\
				}
				






extern void HC595_Set_Data(u16 dat);
extern void HC595_Init(void);
extern void HC595_SetSR_Data(u16 sdata_in);
extern void HC595_SetLR(void);
extern void HC595_Output_Data(u16 sdata);


  
#endif
