

#include "uart_thread.h"


#define TRANSMIT_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define TRANSMIT_QUEUE_LENGTH                    ( 1 )

void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 128, sizeof(char));
     uart.urQueue = xQueueCreate( 128, sizeof(char));
}

void uart_send(char data){
    struct uart_message *putMessage;
    uMessage.data = data;
    putMessage = &uMessage;
	xQueueSendToBack( uart.utQueue, ( void * ) &putMessage, (BaseType_t) 0);
}

void uart_receive(char data){
    struct uart_message *purMessage;
    uMessage.data = data;
    purMessage = &uMessage;
	xQueueSendToBack( uart.utQueue, ( void * ) &purMessage, (BaseType_t) 0);
}

struct uart_message * uart_receive_from_transmit_queue(void){
    struct uart_message *inMessage;
	if(xQueueReceive( uart.utQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

struct uart_message * uart_receive_from_receive_queue(void){
    struct uart_message *inMessage;
	if(xQueueReceive( uart.urQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(const char *string){
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

void transmitUARTchar(char data){
    uart_send(data);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    return;
}

void UART(void){
    initializeUART();
    for(;;){
        //UART_TRANSMIT_MESSAGE = uart_receive_from_transmit_queue();
        //uart.transmit_char = UART_TRANSMIT_MESSAGE->data;
        
    }
}
/*******************************************************************************
 End of File
 */