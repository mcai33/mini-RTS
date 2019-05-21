#include "drv_ds1302.h"
#include "drv_common.h"

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
#define	RTC_ADDR_WP	0x0E		/* Address of write-protect register */
#define RTC_ADDR_TCR	0x10		/* Address of trickle charge register */


#define RTC_ADDR_RAM0	0x20		/* Address of RAM0 */
#define RTC_RAM_SIZE	0x31		/* Address of RAM0 */


#define RTC_CLKBURST 0x3E
#define RTC_RAMBURST 0x7E

//
#define CMD_WRITE_ENABLE 0x00
#define CMD_READ_ONLY 0x80




#define DS1302_SEC				0x80
#define DS1302_MIN				0x82
#define DS1302_HOUR				0x84
#define DS1302_DATE				0x86
#define DS1302_MONTH				0x88
#define DS1302_DAY				0x8A
#define DS1302_YEAR				0x8C
#define DS1302_CONTROL				0x8E
#define DS1302_CHARGER				0x90
#define DS1302_CLKBURST				0xBE
#define DS1302_RAMBURST 			0xFE




#define RAMSIZE 				0x31	// ?????? RAM ? ??????
#define RAMSTART				0xC0 	// ?????? ????? RAM


#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

static void DS1302_Init(void)
{
	DS1302_INIT;
	PIN_DS1302_CLK = 0;
	PIN_DS1302_DATA = 0;
	PIN_DS1302_RSTN = 0;
}









static void DS1302_SendCmd(u8 cmd)
{
	u8 i;
	for (i = 0; i < 8; i ++) 
	{	
		PIN_DS1302_DATA = ((cmd >> i) & 0x01 ); 
		PIN_DS1302_CLK = 0;
		sw_delay_1us();
		
		PIN_DS1302_CLK = 1;
		sw_delay_1us();
	}
}



static void DS1302_WriteByte(u8 addr, u8 dat)
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
		sw_delay_1us();
		
		PIN_DS1302_CLK = 1;
		sw_delay_1us();
	}
	
	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	//	DS1302_SDA = 0;
	PIN_DS1302_DATA = 0;
}


/* Sends 'cmd' command and writes in burst mode 'len' bytes from 'pdat' */
static void DS1302_WriteBurst(u8 cmd, u8 len, u8 * pdat)
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
			sw_delay_1us();
			//			DS1302_SCK = 0;
			PIN_DS1302_CLK = 0;
			sw_delay_1us();
			pdat[j] >>= 1;
		}
	}
	
	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	//	DS1302_SDA = 0;
	PIN_DS1302_DATA = 0;
	
	DS1302_WriteByte(RTC_ADDR_WP, CMD_READ_ONLY);			// ???????? ?????? ?? ??????
}


/* Reads a byte from addr */
static u8 DS1302_ReadByte(u8 addr)
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
		if(PIN_DS1302_DATA)
			val |= 0x80;
		PIN_DS1302_CLK = 1;
		sw_delay_1us();
		
		PIN_DS1302_CLK = 0;
		sw_delay_1us();
	}
	DS1302_DATALINE_OCCUPY;

	PIN_DS1302_RSTN = 0;
	PIN_DS1302_DATA = 0;
	return val;
}


/* Sends 'cmd' command and reads in burst mode 'len' bytes into 'pdat' */
static void DS1302_ReadBurst(u8 cmd, u8 len, u8 * pdat) 
{
	u8 i, j;

	//	DS1302_RST = 1;
	PIN_DS1302_RSTN = 1;	
	cmd = cmd | 0x01; 		// Generate read command

	DS1302_SendCmd(cmd);	// Sends burst read command
	
	readSDA();
	for (j = 0; j < len; j ++) {
		pdat[j] = 0;
		for (i = 0; i < 8; i ++) 
		{
			pdat[j] >>= 1;
			//			if(DS1302_SDA)
			if(HAL_GPIO_ReadPin(DS1302_GPIO, DS1302_SDA))
				pdat[j] |= 0x80;

			//			DS1302_SCK = 1;
			PIN_DS1302_CLK = 1;
			sw_delay_1us();
		
			//			DS1302_SCK = 0;
			PIN_DS1302_CLK = 0;
			sw_delay_1us();

		}
	}
	writeSDA();

	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	PIN_DS1302_DATA = 0;
}


/* Writes time byte by byte from 'buf' */
void DS1302_WriteTime(u8 *buf) 
{	
	DS1302_WriteByte(DS1302_CONTROL, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_1us();
	DS1302_WriteByte(DS1302_SEC, 0x80);
	DS1302_WriteByte(DS1302_YEAR, HEX2BCD(buf[1]));
	DS1302_WriteByte(DS1302_MONTH, HEX2BCD(buf[2]));
	DS1302_WriteByte(DS1302_DATE, HEX2BCD(buf[3]));
	DS1302_WriteByte(DS1302_HOUR, HEX2BCD(buf[4]));
	DS1302_WriteByte(DS1302_MIN, HEX2BCD(buf[5]));
	DS1302_WriteByte(DS1302_SEC, HEX2BCD(buf[6]));
	DS1302_WriteByte(DS1302_DAY, HEX2BCD(buf[7]));
	DS1302_WriteByte(DS1302_CONTROL, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_1us();
}


/* Reads time byte by byte to 'buf' */
void DS1302_ReadTime(u8 *buf)  
{ 
   	u8 tmp;
	
	tmp = DS1302_ReadByte(DS1302_YEAR); 	
	buf[1] = BCD2HEX(tmp);		 
	tmp = DS1302_ReadByte(DS1302_MONTH); 	
	buf[2] = BCD2HEX(tmp);	 
	tmp = DS1302_ReadByte(DS1302_DATE); 	
	buf[3] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(DS1302_HOUR);		
	buf[4] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(DS1302_MIN);		
	buf[5] = BCD2HEX(tmp); 
	tmp = DS1302_ReadByte((DS1302_SEC)) & 0x7F;
	buf[6] = BCD2HEX(tmp);
	tmp = DS1302_ReadByte(DS1302_DAY);		
	buf[7] = BCD2HEX(tmp);
}


/* ????????????? */
void DS1302_Init(void)
{
	DWT_Delay_Init(); //????????????? ??????? ??? ??????? ??????????

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = DS1302_SCLK | DS1302_SDA | DS1302_RST;
	GPIO_InitStructure.Mode =  GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DS1302_GPIO, &GPIO_InitStructure);
	
	DS1302_WriteByte(DS1302_CHARGER, 0x00);			// ????????? Trickle Charger
		
	//	DS1302_RST = 0;
	PIN_DS1302_RSTN = 0;
	//	DS1302_SCK = 0;
	PIN_DS1302_CLK = 0;

	sw_delay_1us(10); // ?????? 10 ??? ?????? ?? ?????.
	DS1302_ClockStart();
}


/* Writes 'val' to ram address 'addr' */
/* Ram addresses range from 0 to 30 */
void DS1302_WriteRam(u8 addr, u8 val) {
	DS1302_WriteByte(DS1302_CONTROL, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_1us();
	if (addr >= RAMSIZE) {
		return;
	}
	
	DS1302_WriteByte(DS1302_RAMSTART + (2 * addr), val);	
	
	DS1302_WriteByte(DS1302_CONTROL, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_1us();
}


/* Reads ram address 'addr' */
u8 DS1302_ReadRam(u8 addr) {
	if (addr >= RAMSIZE) {
		return 0;
	}
	
	return DS1302_ReadByte(DS1302_RAMSTART + (2 * addr));	
}


/* Clears the entire ram writing 0 */
void DS1302_ClearRam(void) {
	u8 i;
	for(i=0; i< RAMSIZE; i++){
		DS1302_WriteRam(i, 0x00);
	}
}


/* Reads time in burst mode, includes control byte */
void DS1302_ReadTimeBurst(u8 * buf) {
	u8 pdat[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	
	DS1302_ReadBurst(DS1302_CLKBURST, 8, pdat); 
	
	buf[1] = BCD2HEX(pdat[6]);	// Year
	buf[2] = BCD2HEX(pdat[4]);	// Month
	buf[3] = BCD2HEX(pdat[3]);	// Date
	buf[4] = BCD2HEX(pdat[2]);	// Hour
	buf[5] = BCD2HEX(pdat[1]);	// Min
	buf[6] = BCD2HEX(pdat[0]);	// Sec
	buf[7] = BCD2HEX(pdat[5]);	// Day
	buf[0] = pdat[7]; 			// Control
}


/* Writes time in burst mode, includes control byte */
void DS1302_WriteTimeBurst(u8 * buf) {
	u8 pdat[8];
	
	pdat[0]=HEX2BCD(buf[6]);	// Sec
	pdat[1]=HEX2BCD(buf[5]);	// Min
	pdat[2]=HEX2BCD(buf[4]);	// Hour
	pdat[3]=HEX2BCD(buf[3]);	// Date
	pdat[4]=HEX2BCD(buf[2]);	// Month
	pdat[5]=HEX2BCD(buf[7]);	// Day
	pdat[6]=HEX2BCD(buf[1]);	// Year
	pdat[7]=buf[0];				// Control
	
	DS1302_WriteBurst(DS1302_CLKBURST, 8, pdat); 
}


/* Reads ram in burst mode 'len' bytes into 'buf' */
void DS1302_ReadRamBurst(u8 len, u8 * buf) {
	u8 i;
	if(len <= 0) {
		return;
	}
	if (len > RAMSIZE) {
		len = RAMSIZE;
	}
	for(i = 0; i < len; i++) {
		buf[i] = 0;
	}
	DS1302_ReadBurst(DS1302_RAMBURST, len, buf);	
}


/* Writes ram in burst mode 'len' bytes from 'buf' */
void DS1302_WriteRamBurst(u8 len, u8 * buf) {
	if(len <= 0) {
		return;
	}
	if (len > RAMSIZE) {
		len = RAMSIZE;
	}
	DS1302_WriteBurst(DS1302_RAMBURST, len, buf);
}


//?????? ?????.
//?????????? DS1302 ? ?????? HALT (???????????, ????? ????????????????).
//???? ??????? ?????? ??????? ?????????? ?????????? ????????? ??? ???????.
void DS1302_ClockStart(void)
{
	u8 buf = 0x00;

	DS1302_WriteByte(DS1302_CONTROL, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_1us();

	buf = DS1302_ReadByte(DS1302_SEC) & 0x7F;		// ?????????? ? 8 ??? 0. ??? ???? ????????? ????????????? ???????? ??????.
	DS1302_WriteByte(DS1302_SEC, buf);

	DS1302_WriteByte(DS1302_CONTROL, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_1us();
}


//????????? ?????.
//??? ???????? ?????? HALT (????????????????). ???????? ??? ??????? ?????? ?????????? :)
void DS1302_ClockStop(void)
{
	u8 buf = 0x00;

	DS1302_WriteByte(DS1302_CONTROL, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_1us();

	buf = DS1302_ReadByte(DS1302_SEC) | 0x80;		// ?????????? ? 8 ??? 1. ??? ???? ????????? ????????????? ???????? ??????.
	DS1302_WriteByte(DS1302_SEC, buf);

	DS1302_WriteByte(DS1302_CONTROL, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_1us();
}


//????? ?????
//?????????? 0 ?? ??? ???????? ????? (? 80h ?? 8Ch ????????????) ? ????????? DS1302 ? ????? HALT (????????????????).
//??? ??????? ????? ????????? ??????? DS1302_ClockStart();
void DS1302_ClockClear(void)
{
	DS1302_WriteByte(DS1302_CONTROL, 0x00);			// ????????? ?????? ?? ??????
	sw_delay_1us();

	DS1302_WriteByte(DS1302_SEC, 0x80);				//????? ?????? ? ??????? ? ????? HALT
	DS1302_WriteByte(DS1302_MIN, 0x00);
	DS1302_WriteByte(DS1302_HOUR, 0x00);
	DS1302_WriteByte(DS1302_DATE, 0x00);
	DS1302_WriteByte(DS1302_MONTH, 0x00);
	DS1302_WriteByte(DS1302_DAY, 0x00);
	DS1302_WriteByte(DS1302_YEAR, 0x00);

	DS1302_WriteByte(DS1302_CONTROL, 0x80);			// ???????? ?????? ?? ??????
	sw_delay_1us();
}
