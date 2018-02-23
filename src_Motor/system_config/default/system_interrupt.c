/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "motor_controller.h"
#include "motor_queue.h"
#include "uart_thread.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void IntHandlerDrvUsartInstance0(void)
{
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT)){
        /* Disable the interrupt, to avoid calling ISR continuously*/
        
        SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
        /* Clear up the interrupt flag */
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
        int i = 0;
        struct uart_message *UART_TRANSMIT_MESSAGE;
        for(i = 0; i < 8; i++){
            if(uxQueueMessagesWaiting( uart.utQueue ) > 0){
            UART_TRANSMIT_MESSAGE = uart_receive_from_transmit_queue();
            PLIB_USART_TransmitterByteSend(USART_ID_1, UART_TRANSMIT_MESSAGE->data);
            }
        }
    }
    DRV_USART_TasksError(sysObj.drvUsart0);
    
    /* This is the USART Driver Receive tasks routine. If the receive
       interrupt flag is set, the tasks routines are executed.
     */

    /* Reading the receive interrupt flag */
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_RECEIVE))
    {

        /* Clear up the interrupt flag */
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
        int i = 0;
        struct uart_message *UART_RECEIVE_MESSAGE;
        for(i = 0; i < 8; i++){
            if(PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)){
                uart_receive(PLIB_USART_ReceiverByteReceive(USART_ID_1));
            }
        }
    }
    
    
}
 
 


 

 

 

 

 
 
 

void IntHandlerDrvTmrInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
    encoder.TIME_TO_CALCULATE = true;
    motor.TIME_TO_SEND = true;
    motor.MOTOR_DEMO_COUNT++;
}
void IntHandlerDrvTmrInstance1(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
    //Comm Error to server
}
void IntHandlerDrvTmrInstance2(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_4);
    //Comm Error to server
}
 
 /*******************************************************************************
 End of File
*/
