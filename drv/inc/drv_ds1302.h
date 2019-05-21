#ifndef __DRV_DS1302__H
#define __DRV_DS1302__H

#include "nuc123.h"
#include "type.h"
#include "drv_common.h"


//PINs are necessary
#define PIN_DS1302_CLK PB7
#define PIN_DS1302_DATA PB6
#define PIN_DS1302_RSTN PB10


//PINs are optional

//#define VAL_PIN_DS1302_DATA GPIO_GET_IN_DATA(PB6)


#define DS1302_INIT  {\
					SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB6_Msk  |SYS_GPB_MFP_PB7_Msk |SYS_GPB_MFP_PB10_Msk );\
					SYS->GPB_MFP |= (SYS_GPB_MFP_PB6_GPIO  |SYS_GPB_MFP_PB7_GPIO |SYS_GPB_MFP_PB0_GPIO);\
					GPIO_SetMode(PB,BIT6 |BIT7 |BIT10,GPIO_PMD_OUTPUT);\
				}
				

#define DS1302_DATALINE_OCCUPY  {\
					SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB6_Msk);\
					SYS->GPB_MFP |= (SYS_GPB_MFP_PB6_GPIO);\
					GPIO_SetMode(PB, BIT6, GPIO_PMD_OUTPUT);\
					PIN_DS1302_DATA = 1;\
				}

#define DS1302_DATALINE_RELEASE  {\
					SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB6_Msk);\
					SYS->GPB_MFP |= (SYS_GPB_MFP_PB6_GPIO);\
					GPIO_SetMode(PB, BIT6, GPIO_PMD_INPUT);\
				}

extern void DS1302_Init(void);



  
#endif
