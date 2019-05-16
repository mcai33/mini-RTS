// 硬件相关定义, 请根据实际硬件修改本文件
#include "nuc123.h"

#define		DELAY		{ UINT8 i=12;while(i--); }	

typedef unsigned char   UINT8;
typedef unsigned short  UINT16;	



#define CH455_INIT {\
										SYS->GPA_MFP &= ~(SYS_GPA_MFP_PA10_Msk | SYS_GPA_MFP_PA11_Msk);\
										SYS->GPA_MFP |= (SYS_GPA_MFP_PA10_GPIO | SYS_GPA_MFP_PA11_GPIO);\
										SYS->ALT_MFP &= ~(SYS_ALT_MFP_PA10_Msk | SYS_ALT_MFP_PA11_Msk);\
										SYS->ALT_MFP |= (SYS_ALT_MFP_PA10_GPIO | SYS_ALT_MFP_PA11_GPIO);\
										GPIO_SetMode(PA,BIT10|BIT11,GPIO_PMD_OUTPUT);\
										SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB14_Msk);\
										SYS->GPB_MFP |= (SYS_GPB_MFP_PB14_INT0);\
										GPIO_SetMode(PB,BIT14,GPIO_PMD_INPUT);\
										GPIO_EnableEINT0(PB, 14, GPIO_INT_FALLING);\
										NVIC_EnableIRQ(EINT0_IRQn);\
										}
					
				

/* 2线接口的连接,与实际电路有关 */
#define	CH455_SCL   PA11 
#define	CH455_SDA   PA10 
#define	CH455_INT   PB14    // 标准的2线接口使用该引脚输出中断

/* 2线接口的位操作,与单片机有关 */
#define		CH455_SCL_SET		{CH455_SCL=1;}
#define		CH455_SCL_CLR		{CH455_SCL=0;}
#define		CH455_SCL_D_OUT		{GPIO_SetMode(PA,BIT11,GPIO_PMD_OUTPUT);}				// 设置SCL为输出方向,对于双向I/O需切换为输出
#define		CH455_SDA_SET		{CH455_SDA=1;}
#define		CH455_SDA_CLR		{CH455_SDA=0;}
#define		CH455_SDA_IN		(CH455_SDA)
#define		CH455_SDA_D_OUT		{GPIO_SetMode(PA,BIT10,GPIO_PMD_OUTPUT);}				// 设置SDA为输出方向,对于双向I/O需切换为输出
#define		CH455_SDA_D_IN		{GPIO_SetMode(PA,BIT10,GPIO_PMD_INPUT);}	// 设置SDA为输入方向,对于双向I/O需切换为输入


/* ********************************************************************************************* */
// 设置系统参数命令

#define CH455_BIT_ENABLE	0x01		// 开启/关闭位
#define CH455_BIT_SLEEP		0x04		// 睡眠控制位
#define CH455_BIT_7SEG		0x08		// 7段控制位
#define CH455_BIT_INTENS1	0x10		// 1级亮度
#define CH455_BIT_INTENS2	0x20		// 2级亮度
#define CH455_BIT_INTENS3	0x30		// 3级亮度
#define CH455_BIT_INTENS4	0x40		// 4级亮度
#define CH455_BIT_INTENS5	0x50		// 5级亮度
#define CH455_BIT_INTENS6	0x60		// 6级亮度
#define CH455_BIT_INTENS7	0x70		// 7级亮度
#define CH455_BIT_INTENS8	0x00		// 8级亮度

#define CH455_SYSOFF	0x0400			// 关闭显示、关闭键盘
#define CH455_SYSON		( CH455_SYSOFF | CH455_BIT_ENABLE )	// 开启显示、键盘
#define CH455_SLEEPOFF	CH455_SYSOFF	// 关闭睡眠
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// 开启睡眠
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// 开启七段模式
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// 开启八段模式
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// 开启显示、键盘、4级亮度
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// 开启显示、键盘、8级亮度


// 加载字数据命令
#define CH455_DIG0		0x1400			// 数码管位0显示,需另加8位数据
#define CH455_DIG1		0x1500			// 数码管位1显示,需另加8位数据
#define CH455_DIG2		0x1600			// 数码管位2显示,需另加8位数据
#define CH455_DIG3		0x1700			// 数码管位3显示,需另加8位数据



// 读取按键代码命令
#define CH455_GET_KEY	0x0700					// 获取按键,返回按键代码


// CH455接口定义
#define		CH455_I2C_ADDR		0x40			// CH455的地址
#define		CH455_I2C_MASK		0x3E			// CH455的高字节命令掩码

// 对外子程序
extern	UINT8 CH455_Read( void );				// 从CH455读取按键代码
extern  void CH455_Write( UINT16 cmd );	// 向CH455发出操作命令
