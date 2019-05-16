/*------------------------------------------------------------------*-
  
   SCH51.H (v1.00)

  ------------------------------------------------------------------

   - see SCH51.C for details


   COPYRIGHT
   ---------

   This code is from the book:

   PATTERNS FOR TIME-TRIGGERED EMBEDDED SYSTEMS by Michael J. Pont 
   [Pearson Education, 2001; ISBN: 0-201-33138-1].

   This code is copyright (c) 2001 by Michael J. Pont.
   
	 

-*------------------------------------------------------------------*/

#ifndef _SCH_H
#define _SCH_H

#include "drv_sch.h"
#include "type.h"
#if 0
typedef uint16_t tByte;
typedef uint16_t tWord;
typedef uint8_t bit;
#endif

#define RETURN_NORMAL (bit) 0
#define RETURN_ERROR (bit) 1

#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK (3)
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER (3)

#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START (4)
#define ERROR_SCH_LOST_SLAVE (5)

#define ERROR_SCH_CAN_BUS_ERROR (6)

#define ERROR_I2C_WRITE_BYTE (10)
#define ERROR_I2C_READ_BYTE (11)
#define ERROR_I2C_WRITE_BYTE_AT24C64 (12)
#define ERROR_I2C_READ_BYTE_AT24C64 (13)
#define ERROR_I2C_DS1621 (14)

#define ERROR_USART_TI (21)
#define ERROR_USART_WRITE_CHAR (22)

#define ERROR_SPI_EXCHANGE_BYTES_TIMEOUT (31)
#define ERROR_SPI_X25_TIMEOUT (32)
#define ERROR_SPI_MAX1110_TIMEOUT (33)

#define ERROR_ADC_MAX150_TIMEOUT (44)
// ------ Public data type declarations ----------------------------

// Store in DATA area, if possible, for rapid access  
// Total memory per task is 7 bytes
typedef struct 
   {
   // Pointer to the task (must be a 'void (void)' function)
   void (*pTask)(void);  

   // Delay (ticks) until the function will (next) be run
   // - see SCH_Add_Task() for further details
   tWord Delay;       

   // Interval (ticks) between subsequent runs.
   // - see SCH_Add_Task() for further details
   tWord Period;       

   // Incremented (by scheduler) when task is due to execute
   tByte RunMe;       
   } sTask; 

// ------ Public function prototypes -------------------------------
// Core scheduler functions
void  SCH_Dispatch_Tasks(void);
tByte SCH_Add_Task(void (*) (void), const tWord, const tWord);  
bit   SCH_Delete_Task(const tByte);
void  SCH_Report_Status(void);

// ------ Public constants -----------------------------------------

// The maximum number of tasks required at any one time
// during the execution of the program
//
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS   (10)   
 
#endif
                              
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/

