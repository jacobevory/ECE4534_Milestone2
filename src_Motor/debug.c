/* ************************************************************************** */
/* Milestone 1 Debug Source */
/* ************************************************************************** */

#include "debug.h"

// Section: Interface Functions                                               */
volatile bool toggleVal = false;
volatile bool toggleVal1 = false;
uint8_t transmitVal = 0;
uint8_t transmitVal1 = 0;

void dbgOutputVal(uint32_t outVal){
    if (outVal < 0 || outVal > 127) transmitVal = 127;
    else transmitVal = (outVal  + (toggleVal * 128));
    writeIntTo1((uint8_t)transmitVal);
    if(!toggleVal) toggleVal = true;
    else if (toggleVal) toggleVal = false;
}

void dbgUARTVal(unsigned char outVal){
        if (!DRV_USART0_TransmitBufferIsFull()) DRV_USART0_WriteByte(outVal);
}

void dbgOutputLoc(uint32_t outVal){
    if (outVal < 0 || outVal > 127) transmitVal1 = 127;
    else transmitVal1 = (outVal  + (toggleVal1 * 128));
    writeIntTo2((uint8_t)transmitVal1);
    if(!toggleVal1) toggleVal1 = true;
    else if (toggleVal1) toggleVal1 = false;
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
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9, array[7]);
}

void UARTstringPLZ(const char *string){
    const char *stringPointer;
    stringPointer = string;
    while(*stringPointer != '\0'){
                PLIB_USART_TransmitterByteSend(USART_ID_1, *stringPointer);
                stringPointer++;
                if(*stringPointer == '\0'){
                    stringPointer = string;
                    return;
                }
    }
}
/*Extra pin map
 
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9, array[7]);
 
 */
/* *****************************************************************************
 End of File
 */
