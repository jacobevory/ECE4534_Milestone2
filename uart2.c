
#include "uart_thread.h"


void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 1024, sizeof(char));
     if(!uart.utQueue) PLIB_USART_TransmitterByteSend(USART_ID_1, 'E');
     uart.urQueue = xQueueCreate( 1024, sizeof(char));
     if(!uart.urQueue) PLIB_USART_TransmitterByteSend(USART_ID_1, 'F');
}

void uart_send(char data){
    uart.transmit_char = data;
	xQueueSendToBack( uart.utQueue, ( void * ) &uart.transmit_char, (BaseType_t) 0);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

char uart_receive(void){
    
    if(uxQueueMessagesWaiting( uart.urQueue )){
        if( xQueueReceive( uart.urQueue, &uart.receive_char, portMAX_DELAY ) ){
            return uart.receive_char;
        }
    }
    return 0;
}

char uart_receive_from_transmit_queue(void){
    if( xQueueReceiveFromISR( uart.utQueue, &uart.transmit_char, pdFALSE ) );
    return uart.transmit_char;
}

void uart_send_to_receive_queue(char data){
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (BaseType_t) 0);
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(char *string){
     char *stringPointer;
    stringPointer = string;
    while(*stringPointer != '\0'){
            uart.transmit_char = *stringPointer;
            xQueueSendToBack( uart.utQueue, ( void * ) &uart.transmit_char, (BaseType_t) 0);
            stringPointer++;
            if(*stringPointer == '\0'){
                stringPointer = string;
                SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
                vTaskDelay(5);
                return;
            }
    }
}

//Depricated, use uart_send(char);
void transmitUARTchar(char data){
    uart_send(data);
    return;
}

void sendMotor(int seq){
    char json[150];
    sprintf(json,"{\"typ\":\"m\",\"rid\":\"1\",\"seq\":\"%d\",\"dil\":\"1\",\"dir\":\"2\",\"spl\":\"1\",\"spr\":\"3\"}", seq);
    transmitUARTstring(json);
}

void sendCol(int seq){
    char json[150];
    sprintf(json,"{\"typ\":\"c\",\"rid\":\"1\",\"seq\":\"%d\",\"col\":\"1\"}", seq);
    transmitUARTstring(json);
}
void sendLine(int seq){
    char json[150];
    sprintf(json,"{\"typ\":\"l\",\"rid\":\"1\",\"seq\":\"%d\",\"li1\":\"1\",\"li2\":\"1\",\"li3\":\"1\",\"li4\":\"1\",\"li5\":\"1\",\"li6\":\"1\",\"li7\":\"1\",\"li8\":\"1\"}", seq);
    transmitUARTstring(json);
}
void sendDist(int seq){
    char json[150];
    sprintf(json,"{\"typ\":\"d\",\"rid\":\"1\",\"seq\":\"%d\",\"id1\":\"1\",\"iu1\":\"2\",\"id2\":\"4\",\"iu2\":\"5\"}", seq);
    transmitUARTstring(json);
}
void sendReq(int seq){
    char json[150];
    sprintf(json,"{\"typ\":\"r\",\"rid\":\"1\",\"seq\":\"%d\"}", seq);
    transmitUARTstring(json);
}


void UART_Tasks(void){
    initializeUART();
    //char *temp = "GET /motor HTTP/1.1\n";//"POST /motor HTTP/1.1\nContent-Type: application/json\nContent-Length: 58\n\n{\"direct1\":\"4\",\"direct2\":\"0\",\"speed1\":\"60\",\"speed2\":\"100\"}\n";
    //transmitUARTstring(temp);
    int d1 = 17;
    int d2 = 18;
    int seq1 = 0;
    int seq2 = 0;
    for(;;){
        
        sendMotor(seq1);
        seq1++;
        vTaskDelay(50);
        sendCol(seq1);
        seq1++;
        vTaskDelay(50);
        sendLine(seq1);
        seq1++;
        vTaskDelay(50);
        sendDist(seq1);
        seq1++;
        vTaskDelay(50);
        sendReq(seq1);
        vTaskDelay(50);
        seq1++;
        
    }
}
/*******************************************************************************
 End of File
 */