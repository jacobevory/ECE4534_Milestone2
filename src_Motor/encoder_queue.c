

#include "encoder_queue.h"


#define QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define QUEUE_LENGTH                    ( 1 )

QueueHandle_t xQueue;


void sensorq_create (void){
	 xQueue = xQueueCreate( 32, sizeof(uint32_t));
}

void sensorq_createf (void){
	 xQueue = xQueueCreate( 32, sizeof(float));
}

void sensorq_send(uint32_t L, uint32_t R){
	//sends data
    struct AMessage *pxMessage;
    xMessage.left  = L;
	xMessage.right = R;
    pxMessage = &xMessage;
	xQueueSendToBackFromISR( xQueue, ( void * ) &pxMessage, (BaseType_t) 0);
}

void sensorq_sendf(float L, float R){
    struct AMessage *pxMessage;
    xMessage.left  = L;
	xMessage.right = R;
    pxMessage = &xMessage;
	xQueueSendToBackFromISR( xQueue, ( void * ) &pxMessage, (BaseType_t) 0);
}

void calculate_encoder_val(void){
    Val1 = (float)sensor.left20Count*100/4;
    Val2 = (float)sensor.right20Count*100/4; // x/(20*.2) = 4
    sensorq_sendf(Val1, Val2);
    sensor.left20Count = 0;
    sensor.right20Count = 0;
    }

struct AMessage* sensorq_receive(void){
    struct AMessage *inMessage;
	if(xQueueReceive( xQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

/*******************************************************************************
 End of File
 */