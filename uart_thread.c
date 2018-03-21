
#include "uart_thread.h"

void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 256, sizeof(char));
     uart.urQueue = xQueueCreate( 1024, sizeof(char));
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
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (TickType_t) 0);
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(char *string){
    char *stringPointer;
    stringPointer = string;
    while(*stringPointer != '\0'){
            uart.transmit_char = *stringPointer;
            xQueueSend( uart.utQueue, ( void * ) &uart.transmit_char, (TickType_t) 0);
            stringPointer++;
           
    }
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

//Depricated, use uart_send(char);
void transmitUARTchar(char data){
    uart_send(data);
    return;
}

void UART_Tasks(void){
    uart.ready = true;
    initializeUART();
    int i;
    
  // color_sensor_send(250, 30, 50, 60);
    
    uint32_t gVal = 5;
    uint32_t rVal = 1;
    uint32_t bVal = 2;
    uint32_t cVal = 0;
   // char *temp = "POST /receive HTTP/1.1\nContent-Type: application/json\nContent-Length: 58\n\n{\"red\":\"6\",\"blue\":\"3\",\"green\":\"20\",\"clear\":\"200\"}\n" + 0;
    //transmitUARTstring(temp);
   // for(i = 0; i < 50; i++){
    enum stateVariable { Initialize, Red_Color, Blue_Color, Green_Color, Clear_Color} state, nextState;
    state = Initialize;
    nextState = Red_Color;
    for(;;){
        switch(state){
            case Initialize:{
                uart.etemp0 = "POST /receive HTTP/1.1\nContent-Type: application/json\nContent-Length: 58\n\n{\"red\": \0";
                uart.etemp1[4];
                itoa(uart.etemp1, rVal, 10);
                uart.etemp1[3] = '\0';
                if (rVal < 255){
                    rVal = rVal + 1;
                }
                else {
                    rVal = 0;
                }
                state = nextState;
                break;
           }
            case Red_Color: {
                uart.etemp2 = ",\"blue\": \0";
                uart.etemp3[4];
                itoa(uart.etemp3, bVal, 10);
                uart.etemp3[3] = '\0';
                if (bVal < 255){
                    bVal = bVal + 1;
                }
                else {
                    bVal = 0;
                }
                state = Blue_Color;
                break;
            }
            case Blue_Color: {
                uart.etemp4 = ",\"green\": \0";
                uart.etemp5[4];
                itoa(uart.etemp5, gVal, 10);
                uart.etemp5[3] = '\0';
                if (gVal < 255){
                    gVal = gVal + 1;
                }
                else {
                    gVal = 0;
                }
                state = Green_Color;
                break;
            }
            case Green_Color: {
                uart.etemp6 = ",\"clear\": \0";
                uart.etemp7[4];
                itoa(uart.etemp7, cVal, 10);
                uart.etemp7[7] = '\0';
                if (cVal < 255){
                    cVal = cVal + 1;
                }
                else {
                    cVal = 0;
                }
                state = Clear_Color;
                break;
            }
            case Clear_Color: {
                transmitUARTstring(uart.etemp0);
                 
                transmitUARTstring(uart.etemp1);
         
                transmitUARTstring(uart.etemp2);
             
                transmitUARTstring(uart.etemp3);
                
                transmitUARTstring(uart.etemp4);
                
                transmitUARTstring(uart.etemp5);
                 
                transmitUARTstring(uart.etemp6);
                
                transmitUARTstring(uart.etemp7);
                uart_send('}');
                vTaskDelay(20); 
                state = Initialize;
                break;
            }
           
       // }
        }
    }
   // initializeUART();
    //char *temp = "POST /receive HTTP/1.1\nContent-Type: application/json\nContent-Length: 58\n\n{\"red\":\"6\",\"blue\":\"3\",\"green\":\"20\",\"clear\":\"200\"}\n" + 0;
    //transmitUARTstring(temp);
    
}
/*******************************************************************************
 End of File
 */