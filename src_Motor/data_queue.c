#include "data_queue.h"

void initializeDataQueue(void){
    data_queue_create();
}

void data_queue_create(void){
     data.dataQueue = xQueueCreate( 32, 256);
}
void encoder_data_send(float L, float R){
    struct data_message *pdataMessage;
    dataMessage.messageType = Encoder;
    dataMessage.left  = L;
	dataMessage.right = R;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void distance_data_send(uint32_t d){
    struct data_message *pdataMessage;
    dataMessage.messageType = Distance;
    dataMessage.distance = d;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void color_data_send(int8_t c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Color;
    dataMessage.color = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void line_data_send(uint8_t l){
    struct data_message *pdataMessage;
    dataMessage.messageType = Line;
    dataMessage.line = l;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void motor_data_send(uint32_t speed_left, uint32_t speed_right, bool direction_left, bool direction_right){
    struct data_message *pdataMessage;
    dataMessage.messageType = Motor;
    dataMessage.speed_left = speed_left;
    dataMessage.speed_right = speed_right;
    dataMessage.direction_left = direction_left;
    dataMessage.direction_right = direction_right;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void uart_data_send_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_send;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void uart_data_receive_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_receive;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void encoder_counter_rollover_error(void){
    struct data_message *pdataMessage;
    dataMessage.messageType = Rollover_error;
    pdataMessage = &dataMessage;
	xQueueSendToBackFromISR( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

struct data_message * data_receive( void ){
    struct data_message *inMessage;
	if(xQueueReceive( data.dataQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}
/*******************************************************************************
 End of File
 */