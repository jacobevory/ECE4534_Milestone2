

#include "line_sensor_queue.h"


#define LINE_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define LINE_QUEUE_LENGTH                    ( 1 )

void line_sensor_create (void){
	 line.lQueue = xQueueCreate( 32, sizeof(bool));
}

void line_sensor_send(bool s1, bool s2, bool s3, bool s4, bool s5, bool s6, bool s7){
    struct line_message *plMessage;
    plMessage = &lMessage;
	xQueueSendToBack( line.lQueue, ( void * ) &plMessage, (BaseType_t) 0);
}

struct line_message* line_sensor_receive(void){
    struct line_message *inMessage;
	if(xQueueReceive( line.lQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void initializeLineSensor(void){
    line_sensor_create();
}

void LINE_SENSOR(void){
    initializeLineSensor();
    struct line_message *LINE_MESSAGE;
    
    for(;;){
        if(uxQueueMessagesWaiting( line.lQueue ) > 0){
            LINE_MESSAGE = line_sensor_receive();
        }
    }
}
/*******************************************************************************
 End of File
 */