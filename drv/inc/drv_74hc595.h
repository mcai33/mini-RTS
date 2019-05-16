#ifndef __DRV_74HC595__H
#define __DRV_74HC595__H

#include "nuc123.h"
#include "type.h"

#define PIN_HC575_SI PC3
#define PIN_HC575_LCK PC2
#define PIN_HC575_SCK PC1
#define PIN_HC575_RST_N PC0
//#define PIN_HC575_OE_N PC4

extern void HC575_Set_Data(uint16_t dat);
extern void HC575_Init(void);
extern void HC575_SetSR_Data(uint16_t sdata_in);
extern void HC575_SetLR(void);
extern void HC575_Output_Data(uint16_t sdata);


  
#endif
