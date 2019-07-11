#include "drv_ds1302.h"
#include "drv_common.h"
#include <stdio.h>



//register addr map
#define	RTC_CMD_READ	0x81		/* Read command */
#define	RTC_CMD_WRITE	0x80		/* Write command */

#define	RTC_ADDR_SEC	0x00		/* Address of second register */
#define	RTC_ADDR_MIN	0x02		/* Address of minute register */
#define	RTC_ADDR_HOUR	0x04		/* Address of hour register */
#define	RTC_ADDR_DATE	0x06		/* Address of day of month register */
#define	RTC_ADDR_MON	0x08 		/* Address of month register */
#define	RTC_ADDR_DAY	0x0A		/* Address of day of week register */
#define	RTC_ADDR_YEAR	0x0C		/* Address of year register */
#define	RTC_ADDR_WP		0x0E		/* Address of write-protect register */
#define RTC_ADDR_TCR	0x10		/* Address of trickle charge register */


#define RTC_ADDR_RAM0	0x20		/* Address of RAM0 */
#define RTC_RAM_SIZE	0x31		/* Size of RAM0 */


#define RTC_CLKBURST 0x3E
#define RTC_RAMBURST 0x7E


//
#define CMD_WRITE_ENABLE 0x00
#define CMD_WRITE_DISABLE 0x80



#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

void DS1302_Init(void)
{
	DS1302_INIT;
	PIN_DS1302_CLK = 0;
	PIN_DS1302_DATA = 0;
	PIN_DS1302_RSTN = 0;
}



#if 1
void DS1302_Test(void)
{
	
	DS1302_Init();
	//DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_WP, CMD_WRITE_ENABLE);
	//DS1302_WriteByte(u8 addr, u8 dat);
	u8 sec,min;
	static u8 first_run = 1;
	if(1 == first_run){
		printf("\n\n");
		printf("+------------------------------------------------------------------------+\n");
		printf("|                      DS1302 Auto Test Code                              |\n");
		printf("+------------------------------------------------------------------------+\n");                    
		printf("Write DS1302 -disable write protect  \n");
		DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_WP, CMD_WRITE_ENABLE);
		printf("Write DS1302 -time stop");
		DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_SEC, 0x80);
		printf("Write DS1302 -write sec and time start \n");
		DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_MIN, 0x00);
		DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_SEC, 0x00);
		DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_WP, CMD_WRITE_DISABLE);
	};
	first_run = 0;
	sec = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_SEC) & 0x7f;
	//sec = BCD2HEX(sec);
	min = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_MIN);
	//min = BCD2HEX(min);
	printf("Read DS1302 -min,sec  %x,%x \n",min,sec);
	//ch = getchar();

}
#endif





 void DS1302_SendCmd(u8 cmd)
{
	u8 i;
	for (i = 0; i < 8; i ++) 
	{	
		PIN_DS1302_DATA = ((cmd >> i) & 0x01 ); 
		PIN_DS1302_CLK = 0;
		sw_delay_us(5);
		
		PIN_DS1302_CLK = 1;
		sw_delay_us(5);
	}
}



 void DS1302_WriteByte(u8 addr, u8 dat)
{
	u8 i;

	//	DS1302_RST = 1;
	PIN_DS1302_RSTN = 1;	
	
	//	addr = addr & 0xFE;
	DS1302_SendCmd(addr);	
	
	for (i = 0; i < 8; i ++) 
	{
		PIN_DS1302_DATA = ((dat >> i) & 0x01 ); 
		PIN_DS1302_CLK = 0;
		sw_delay_us(5);
		
		PIN_DS1302_CLK = 1;
		sw_delay_us(5);
	}
	
	//	DS1302_RST = 0;
	
	PIN_DS1302_RSTN = 0;
	PIN_DS1302_CLK = 0;
	PIN_DS1302_DATA = 0;
}


/* Sends 'cmd' command and writes in burst mode 'len' bytes from 'pdat' */
 void DS1302_WriteBurst(u8 cmd, u8 len, u8 * pdat)
{
	u8 i, j;
	
	DS1302_WriteByte(RTC_ADDR_WP, CMD_WRITE_ENABLE);			// ????????? ?????? ?? ??????

	//	DS1302_RST = 1;
	PIN_DS1302_RSTN = 1;	
	
	DS1302_SendCmd(cmd);	// Sends burst write command
	
	for(j = 0; j < len; j++)
	{
		for (i = 0; i < 8; i ++) 
		{
			//			DS1302_SDA = (bit)(d & 1);
			PIN_DS1302_DATA = ((pdat[j] >> i) & 0x01 ); 
			//			DS1302_SCK = 1;
			PIN_DS1302_CLK = 1;
			sw_delay_us(5);
			//			DS1302_SCK = 0;
			PIN_DS1302_CLK = 0;
			sw_delay_us(5);
			pdat[j] >>= 1;
		}
	}
	
	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	//	DS1302_SDA = 0;
	PIN_DS1302_DATA = 0;
	
	DS1302_WriteByte(RTC_ADDR_WP, CMD_WRITE_DISABLE);			// ???????? ?????? ?? ??????
}


/* Reads a byte from addr */
 u8 DS1302_ReadByte(u8 addr)
{
	u8 i;
	u8 val = 0;

	//	DS1302_RST = 1;
	PIN_DS1302_RSTN = 1;	

	DS1302_SendCmd(addr);	// Sends address
	
	DS1302_DATALINE_RELEASE;
	for (i = 0; i < 8; i ++) 
	{
		val >>= 1;
		PIN_DS1302_CLK = 1;
		sw_delay_us(5);
		
		PIN_DS1302_CLK = 0;
		sw_delay_us(2);
		
		if(PIN_DS1302_DATA){
			val |= 0x80;		
		}
		else{
			val &= 0x7f;
		}
		sw_delay_us(3);
	}
	DS1302_DATALINE_OCCUPY;

	PIN_DS1302_RSTN = 0;
	PIN_DS1302_DATA = 0;
	return val;
}


/* Sends 'cmd' command and reads in burst mode 'len' bytes into 'pdat' */
 void DS1302_ReadBurst(u8 cmd, u8 len, u8 * pdat) 
{
	u8 i, j;

	//	DS1302_RST = 1;
	PIN_DS1302_RSTN = 1;	
	cmd = cmd | 0x01; 		// Generate read command

	DS1302_SendCmd(cmd);	// Sends burst read command
	
	DS1302_DATALINE_RELEASE;
	for (j = 0; j < len; j ++) {
		pdat[j] = 0;
		for (i = 0; i < 8; i ++) 
		{
			pdat[j] >>= 1;
			//			if(DS1302_SDA)
			if(PIN_DS1302_DATA)
				pdat[j] |= 0x80;

			//			DS1302_SCK = 1;
			PIN_DS1302_CLK = 1;
			sw_delay_us(5);
		
			//			DS1302_SCK = 0;
			PIN_DS1302_CLK = 0;
			sw_delay_us(5);

		}
	}
	DS1302_DATALINE_OCCUPY;

	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	PIN_DS1302_DATA = 0;
}

/* Writes time byte by byte from 'buf' */
void DS1302_WriteTime(u8 *buf) 
{	
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_WP, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_us(5);
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_SEC, 0x80);
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_YEAR, HEX2BCD(buf[1]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_MON, HEX2BCD(buf[2]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_DATE, HEX2BCD(buf[3]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_HOUR, HEX2BCD(buf[4]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_MIN, HEX2BCD(buf[5]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_SEC, HEX2BCD(buf[6]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_DAY, HEX2BCD(buf[7]));
	DS1302_WriteByte(RTC_CMD_WRITE | RTC_ADDR_WP, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_us(5);
}


/* Reads time byte by byte to 'buf' */
void DS1302_ReadTime(u8 *buf)  
{ 
   	u8 tmp;
	
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_YEAR); 	
	buf[1] = BCD2HEX(tmp);		 
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_MON); 	
	buf[2] = BCD2HEX(tmp);	 
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_DATE); 	
	buf[3] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_HOUR);		
	buf[4] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_MIN);		
	buf[5] = BCD2HEX(tmp); 
	tmp = DS1302_ReadByte((RTC_CMD_READ | RTC_ADDR_SEC)) & 0x7F;
	buf[6] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(RTC_CMD_READ | RTC_ADDR_DAY);		
	buf[7] = BCD2HEX(tmp);
}


