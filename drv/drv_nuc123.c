#include "drv_nuc123.h"
#include "nuc123.h"
#include "hid_transfer.h"

void MCU_Init(void)
{
   // CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(USBD_MODULE);

    /* Select module clock source */
   // CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));
    CLK_SetModuleClock(USBD_MODULE, 0, CLK_CLKDIV_USB(3));
	
    /* Open USB controller */
    USBD_Open(&gsInfo, HID_ClassRequest, NULL);

    /*Init Endpoint configuration for HID */
    HID_Init();

    /* Start USB device */
    USBD_Start();

    /* Enable USB device interrupt */
    NVIC_EnableIRQ(USBD_IRQn);
//void USBD_Start(void);
//void USBD_GetSetupPacket(uint8_t *buf);
//void USBD_ProcessSetupPacket(void);
//void USBD_StandardRequest(void);
//void USBD_PrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size);
//void USBD_CtrlIn(void);
//void USBD_PrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size);
//void USBD_CtrlOut(void);
//void USBD_SwReset(void);
//void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq);
//void USBD_SetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback);
//void USBD_LockEpStall(uint32_t u32EpBitmap);
//	

}