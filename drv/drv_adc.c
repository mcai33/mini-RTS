#include "drv_adc.h"
#include "nuc123.h"


#define ADC_SAMPLE_COUNT 16
volatile uint8_t g_u8ADF;


void ADC_IRQHandler(void)
{
    uint32_t u32Flag;
    /* Get ADC conversion finish interrupt flag */
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    /* Check ADC conversion finish */
    if (u32Flag & ADC_ADF_INT)
        g_u8ADF = 1;
    /* Clear conversion finish flag */
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}

void ADC_Init(void)
{
    /* Enable ADC module clock */
    CLK_EnableModuleClock(ADC_MODULE);

    /* ADC clock source is 22.1184MHz, set divider to 7, ADC clock is 22.1184/7 MHz */
    CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HXT, CLK_CLKDIV_ADC(2));
	
		SYS->GPF_MFP &= ~(SYS_GPF_MFP_PF3_Msk);
		SYS->GPF_MFP |= (SYS_GPF_MFP_PF3_ADC7);

		SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PF3_Msk);
		SYS->ALT_MFP1 |= SYS_ALT_MFP1_PF3_ADC7;

		GPIO_DISABLE_DIGITAL_PATH(PF, BIT3);

	
	
		ADC_Open(ADC, NULL, ADC_ADCR_ADMD_CONTINUOUS, BIT7);

		/* Power on ADC module */
		ADC_POWER_ON(ADC);

		/* Clear the A/D interrupt flag for safe */
		ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

		/* Enable ADC conversion finish interrupt */
		ADC_EnableInt(ADC, ADC_ADF_INT);
		NVIC_EnableIRQ(ADC_IRQn);

}

uint32_t GetAVDDCodeByADC(void)
{
    uint32_t u32Count, u32Sum=0, u32Data=0;

    /* sample times are according to ADC_SAMPLE_COUNT definition */
    for (u32Count = 0; u32Count < ADC_SAMPLE_COUNT; u32Count++)
    {
        /* Delay for band-gap voltage stability */
        CLK_SysTickDelay(100);
        while (ADC_IS_BUSY(ADC));

        /* Start A/D conversion */
        ADC_START_CONV(ADC);

        u32Data = 0;
        /* Wait conversion done */
        while (g_u8ADF == 0);
        g_u8ADF = 0;

        /* Get the conversion result */
        u32Data = ADC_GET_CONVERSION_DATA(ADC, 7);

        /* Stop A/D conversion */
        ADC_STOP_CONV(ADC);
        /* Sum each conversion data */
        u32Sum += u32Data;
    }

    /* Return the average of ADC_SAMPLE_COUNT samples */
    return (u32Sum >> 4);
}
