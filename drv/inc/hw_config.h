#ifndef __HW_CONFIG__H
#define __HW_CONFIG__H
#include "nuc123.h"

typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;

#define HC595


#ifdef HC595
#define PIN_HC575_SI PC3
#define PIN_HC575_LCK PC2
#define PIN_HC575_SCK PC1
#define PIN_HC575_RST_N PC0
//#define PIN_HC575_OE_N PC4
#endif



#endif

