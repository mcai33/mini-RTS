#include "drv_mcp7425.h"
#include "hal_i2c.h"
#include "stdio.h"



void MCP7425_Init(void)
{
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


	    /* Set GPF multi-function pins for I2C0 SDA and SCL */
    SYS->GPF_MFP &= ~(SYS_GPF_MFP_PF2_Msk | SYS_GPF_MFP_PF3_Msk);
    SYS->GPF_MFP |= (SYS_GPF_MFP_PF2_I2C0_SDA | SYS_GPF_MFP_PF3_I2C0_SCL);
    SYS->ALT_MFP1 &= ~(SYS_ALT_MFP1_PF2_Msk | SYS_ALT_MFP1_PF3_Msk);
    SYS->ALT_MFP1 |= (SYS_ALT_MFP1_PF2_I2C0_SDA | SYS_ALT_MFP1_PF3_I2C0_SCL);

    printf("\n");
    printf("Check I2C Slave(I2C0) is running first!\n");
    printf("Press any key to continue.\n");
   // getchar();

    /* Access Slave with no address */
    printf("\n");
    printf(" == No Mask Address ==\n");
    I2C0_Read_Write_SLAVE(0x15);
    I2C0_Read_Write_SLAVE(0x35);
    I2C0_Read_Write_SLAVE(0x55);
    I2C0_Read_Write_SLAVE(0x75);
    printf("SLAVE Address test OK.\n");

    /* Access Slave with address mask */
    printf("\n");
    printf(" == Mask Address ==\n");
    I2C0_Read_Write_SLAVE(0x15 & ~0x01);
    I2C0_Read_Write_SLAVE(0x35 & ~0x04);
    I2C0_Read_Write_SLAVE(0x55 & ~0x01);
    I2C0_Read_Write_SLAVE(0x75 & ~0x04);
    printf("SLAVE Address Mask test OK.\n");

    //s_I2C0HandlerFn = NULL;

    /* Close I2C0 */
    I2C0_Close();
	

}
