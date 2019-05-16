// Ӳ����ض���, �����ʵ��Ӳ���޸ı��ļ�
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
					
				

/* 2�߽ӿڵ�����,��ʵ�ʵ�·�й� */
#define	CH455_SCL   PA11 
#define	CH455_SDA   PA10 
#define	CH455_INT   PB14    // ��׼��2�߽ӿ�ʹ�ø���������ж�

/* 2�߽ӿڵ�λ����,�뵥Ƭ���й� */
#define		CH455_SCL_SET		{CH455_SCL=1;}
#define		CH455_SCL_CLR		{CH455_SCL=0;}
#define		CH455_SCL_D_OUT		{GPIO_SetMode(PA,BIT11,GPIO_PMD_OUTPUT);}				// ����SCLΪ�������,����˫��I/O���л�Ϊ���
#define		CH455_SDA_SET		{CH455_SDA=1;}
#define		CH455_SDA_CLR		{CH455_SDA=0;}
#define		CH455_SDA_IN		(CH455_SDA)
#define		CH455_SDA_D_OUT		{GPIO_SetMode(PA,BIT10,GPIO_PMD_OUTPUT);}				// ����SDAΪ�������,����˫��I/O���л�Ϊ���
#define		CH455_SDA_D_IN		{GPIO_SetMode(PA,BIT10,GPIO_PMD_INPUT);}	// ����SDAΪ���뷽��,����˫��I/O���л�Ϊ����


/* ********************************************************************************************* */
// ����ϵͳ��������

#define CH455_BIT_ENABLE	0x01		// ����/�ر�λ
#define CH455_BIT_SLEEP		0x04		// ˯�߿���λ
#define CH455_BIT_7SEG		0x08		// 7�ο���λ
#define CH455_BIT_INTENS1	0x10		// 1������
#define CH455_BIT_INTENS2	0x20		// 2������
#define CH455_BIT_INTENS3	0x30		// 3������
#define CH455_BIT_INTENS4	0x40		// 4������
#define CH455_BIT_INTENS5	0x50		// 5������
#define CH455_BIT_INTENS6	0x60		// 6������
#define CH455_BIT_INTENS7	0x70		// 7������
#define CH455_BIT_INTENS8	0x00		// 8������

#define CH455_SYSOFF	0x0400			// �ر���ʾ���رռ���
#define CH455_SYSON		( CH455_SYSOFF | CH455_BIT_ENABLE )	// ������ʾ������
#define CH455_SLEEPOFF	CH455_SYSOFF	// �ر�˯��
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// ����˯��
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// �����߶�ģʽ
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// �����˶�ģʽ
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// ������ʾ�����̡�4������
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// ������ʾ�����̡�8������


// ��������������
#define CH455_DIG0		0x1400			// �����λ0��ʾ,������8λ����
#define CH455_DIG1		0x1500			// �����λ1��ʾ,������8λ����
#define CH455_DIG2		0x1600			// �����λ2��ʾ,������8λ����
#define CH455_DIG3		0x1700			// �����λ3��ʾ,������8λ����



// ��ȡ������������
#define CH455_GET_KEY	0x0700					// ��ȡ����,���ذ�������


// CH455�ӿڶ���
#define		CH455_I2C_ADDR		0x40			// CH455�ĵ�ַ
#define		CH455_I2C_MASK		0x3E			// CH455�ĸ��ֽ���������

// �����ӳ���
extern	UINT8 CH455_Read( void );				// ��CH455��ȡ��������
extern  void CH455_Write( UINT16 cmd );	// ��CH455������������