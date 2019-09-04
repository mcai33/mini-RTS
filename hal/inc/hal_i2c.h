#ifndef __HAL_I2C__H
#define __HAL_I2C__H


#include "nuc123.h"





extern void I2C0_Init(void);
extern void I2C0_Close(void);

extern int32_t I2C0_Read_Write_SLAVE(uint8_t slvaddr);

  
#endif
