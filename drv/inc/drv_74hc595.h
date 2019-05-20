#ifndef __DRV_74HC595__H
#define __DRV_74HC595__H

#include "nuc123.h"
#include "type.h"
#include "drv_common.h"


//PINs are necessary
#define PIN_HC575_SI PC3
#define PIN_HC575_LCK PC2
#define PIN_HC575_SCK PC1
				
//PINs are optional
#define PIN_HC575_RST_N PC0
//#define PIN_HC575_OE_N PC4

#define HC575_INIT  {\
					SYS->GPC_MFP &= ~(SYS_GPC_MFP_PC3_Msk |SYS_GPC_MFP_PC2_Msk |SYS_GPC_MFP_PC1_Msk |SYS_GPC_MFP_PC0_Msk );\
					SYS->GPC_MFP |= (SYS_GPC_MFP_PC3_GPIO |SYS_GPC_MFP_PC2_GPIO |SYS_GPC_MFP_PC1_GPIO |SYS_GPC_MFP_PC0_GPIO);\
					GPIO_SetMode(PC,BIT3 |BIT2 |BIT1 |BIT0,GPIO_PMD_OUTPUT);\
				}
				






extern void HC575_Set_Data(u16 dat);
extern void HC575_Init(void);
extern void HC575_SetSR_Data(u16 sdata_in);
extern void HC575_SetLR(void);
extern void HC575_Output_Data(u16 sdata);


  
#endif
