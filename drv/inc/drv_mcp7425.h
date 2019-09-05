#ifndef __DRV_MCP7425__H
#define __DRV_MCP7425__H

#include "nuc123.h"
#include "type.h"
#include "drv_common.h"

#define MCP4725_DA 0x60
#define MCP4725_COMMAND_FAST_MODE 0
#define MCP4725_COMMAND_WRITE_DAC_REG 2
#define MCP4725_COMMAND_WRITE_DAC_REG_AND_EEPROM 3
#define MCP4725_WRITE_BIT 0x00
#define MCP4725_READ_BIT 0x01

typedef u8 mcp4725_mode_t; 
typedef struct  mcp4725_data{
	u8 byte1;
	u8 byte2;
	u8 byte3;
	u8 byte4;
	u8 byte5;
	u8 byte6;
}mcp4725_byte_st;

#endif
