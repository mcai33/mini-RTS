#ifndef __DRV_LED__H
#define __DRV_LED__H
#include "drv_common.h"

#define LED1 0x01
#define LED2 0x02

#define IO_LED1 PA12
#define IO_LED2 PA13

#define LED_ON 1
#define LED_OFF 0

#define LED1_ON() (IO_LED1 = 1)
#define LED1_OFF() (IO_LED1 = 1)
#define LED1_REVERSE() (IO_LED1 = ~IO_LED1)

#define LED2_ON() (IO_LED2 = 1)
#define LED2_OFF() (IO_LED2 = 1)
#define LED2_REVERSE() (IO_LED2 = ~IO_LED2)



extern void DRV_LED_Init(void);


#endif
