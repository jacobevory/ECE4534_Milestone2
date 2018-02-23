/* ************************************************************************** */
/* Milestone 1 Debug Source */
/* ************************************************************************** */

#include "debug.h"

// Section: Interface Functions                                               */
typedef struct {
volatile bool toggleVal;
volatile bool toggleVal1;
uint8_t transmitVal;
uint8_t transmitVal1;
} DEBUG_VARS;
DEBUG_VARS debug;

bool DEBUG_INIT_FLAG = false;

void dbgOutputVal(uint32_t outVal){
    if(!DEBUG_INIT_FLAG){
        debug.toggleVal = false;
        debug.toggleVal1 = false;
        DEBUG_INIT_FLAG = true;
    }
    if (outVal < 0 || outVal > 127) debug.transmitVal = 127;
    else debug.transmitVal = (outVal  + (debug.toggleVal * 128));
    writeIntTo1((uint8_t)debug.transmitVal);
    if(!debug.toggleVal) debug.toggleVal = true;
    else if (debug.toggleVal) debug.toggleVal = false;
}

void dbgUARTVal(unsigned char outVal){
        if (!DRV_USART0_TransmitBufferIsFull()) DRV_USART0_WriteByte(outVal);
}

void dbgOutputLoc(uint32_t outVal){
    if(!DEBUG_INIT_FLAG){
        debug.toggleVal = false;
        debug.toggleVal1 = false;
        DEBUG_INIT_FLAG = true;
    }
    if (outVal < 0 || outVal > 127) debug.transmitVal1 = 127;
    else debug.transmitVal1 = (outVal  + (debug.toggleVal1 * 128));
    writeIntTo2((uint8_t)debug.transmitVal1);
    if(!debug.toggleVal1) debug.toggleVal1 = true;
    else if (debug.toggleVal1) debug.toggleVal1 = false;
}

void ohNoh(void){
    dbgOutputLoc(LOC_127);
    writeIntTo1(0);
    writeIntTo2(0);
    dbgUARTVal('E');
    dbgUARTVal('r');
    dbgUARTVal('r');
    dbgUARTVal('o');
    dbgUARTVal('r');
}

void writeIntTo1(uint8_t value){
    bool array[8];
    int i = 0;
    for (i = 0; i < 8; ++i) {
    array[i] = (value >> i) & 1;
    }
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7, array[7]);
}

void writeIntTo2(uint8_t value){
    bool array[8];
    int i = 0;
    for (i = 0; i < 8; ++i) {
    array[i] = (value >> i) & 1;
    }
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_8, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_14, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15, array[7]);
}

void UARTstringPLZ(const char *string){
    const char *stringPointer;
    stringPointer = string;
    while(*stringPointer == '\0'){
        uart_send(*stringPointer);
        stringPointer++;
            if(*stringPointer == '\0'){
                stringPointer = string;
                SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
                return;
            }
    }
}
/* *****************************************************************************
 End of File
 */
