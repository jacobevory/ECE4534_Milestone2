

#include "encoder_queue.h"


#define ENCODER_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define ENCODER_QUEUE_LENGTH                    ( 1 )

QueueHandle_t eQueue;


/*void sensorq_create (void){
	 eQueue = xQueueCreate( 32, sizeof(uint32_t));
}*/

void encoder_sensor_create (void){
	 eQueue = xQueueCreate( 32, sizeof(float));
}

/*void sensorq_send(uint32_t L, uint32_t R){
	//sends data
    struct encoder_message *peMessage;
    eMessage.left  = L;
	eMessage.right = R;
    peMessage = &eMessage;
	xQueueSendToBackFromISR( eQueue, ( void * ) &peMessage, (BaseType_t) 0);
}*/

void encoder_sensor_send(float L, float R){
    struct encoder_message *peMessage;
    eMessage.left  = L;
	eMessage.right = R;
    peMessage = &eMessage;
	xQueueSendToBackFromISR( eQueue, ( void * ) &peMessage, (BaseType_t) 0);
}

void calculate_encoder_val(void){
    Val1 = (float)sensor.left20Count*100/4;
    Val2 = (float)sensor.right20Count*100/4; // x/(20*.2) = 4
    encoder_sensor_send(Val1, Val2);
    sensor.left20Count = 0;
    sensor.right20Count = 0;
    }

struct encoder_message* encoder_sensor_receive(void){
    struct encoder_message *inMessage;
	if(xQueueReceive( eQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

/*******************************************************************************
 End of File
 */