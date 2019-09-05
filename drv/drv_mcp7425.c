#include "drv_mcp7425.h"
#include "hal_i2c.h"
#include "stdio.h"



void MCP7425_Init(void)
{
	u8 dat[]={0x00,0x00};
    /*
        This sample code sets I2C bus clock to 100kHz. Then, Master accesses Slave with Byte Write
        and Byte Read operations, and check if the read data is equal to the programmed data.
    */
    printf("\n");
    printf("+----------------------------------------------------+\n");
    printf("| I2C Driver Sample Code(Master) for access Slave    |\n");
    printf("| Needs to work with I2C_Slave sample code           |\n");
    printf("|     I2C Master (I2C0) <---> I2C Slave(I2C0)        |\n");
    printf("| !! This sample code requires two borads to test !! |\n");
    printf("+----------------------------------------------------+\n");

    printf("Configure I2C0 as a master.\n");

	/*
IO MAPPING
NUC123.PA10 --- MCP4725.SDA
NUC123.PA11 --- MCP4725.SCL
*/
#if 0
	SYS->GPA_MFP &= ~(SYS_GPA_MFP_PA10_Msk | SYS_GPA_MFP_PA11_Msk );
	SYS->GPA_MFP |= (SYS_GPA_MFP_PA10_I2C0_SDA | SYS_GPA_MFP_PA11_I2C0_SCL );

	SYS->ALT_MFP &= ~(SYS_ALT_MFP_PA10_Msk |SYS_ALT_MFP_PA11_Msk );
	SYS->ALT_MFP |= (SYS_ALT_MFP_PA10_I2C0_SDA |SYS_ALT_MFP_PA11_I2C0_SCL );	
#endif	

	
    I2C0_Init();


    printf("\n");
    printf("Check I2C Slave(I2C0) is running first!\n");
    printf("Press any key to continue.\n");
   // getchar();

    /* Access Slave with no address */
    printf("\n");
	I2C0_Read_Write_SLAVE(MCP4725_DA);
	
   //I2C_WriteMultiBytes(I2C0, 0x60, dat, 2);

    //s_I2C0HandlerFn = NULL;

    /* Close I2C0 */
    I2C0_Close();
	

}


#if 0
int32_t MCP4725_Write(mcp4725_mode_t mode,mcp4725_byte_st byte)
{
		byte.byte1 = (MCP4725_DA << 1) & MCP4725_WRITE_BIT;
		if(mode == MCP4725_COMMAND_FAST_MODE){
			//I2C_WriteMultiBytes(I2C0, byte.byte1, const uint8_t *data, uint32_t u32wLen)
			I2C_WriteByte(I2C0, byte.byte1, byte.byte2);
		}
	
        g_au8MstTxData[0] = (uint8_t)((i & 0xFF00) >> 8);
        g_au8MstTxData[1] = (uint8_t)(i & 0x00FF);
        g_au8MstTxData[2] = (uint8_t)(g_au8MstTxData[1] + 3);

        g_u8MstDataLen = 0;
        g_u8MstEndFlag = 0;

        /* I2C function to write data to slave */
        s_I2C0HandlerFn = (I2C_FUNC)I2C_MasterTx;

        /* I2C as master sends START signal */
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_STA);

        /* Wait I2C Tx Finish */
        while(g_u8MstEndFlag == 0);
        g_u8MstEndFlag = 0;

        /* I2C function to read data from slave */
        s_I2C0HandlerFn = (I2C_FUNC)I2C_MasterRx;

        g_u8MstDataLen = 0;
        g_u8DeviceAddr = slvaddr;

        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_STA);

        /* Wait I2C Rx Finish */
        while(g_u8MstEndFlag == 0);

        /* Compare data */
        if(g_u8MstRxData != g_au8MstTxData[2])
        {
            printf("I2C Byte Write/Read Failed, Data 0x%x\n", g_u8MstRxData);
            return -1;
        }

    printf("Master Access Slave (0x%X) Test OK\n", slvaddr);
    return 0;
}
#endif