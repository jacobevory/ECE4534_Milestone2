

#include "encoder_queue.h"


#define ENCODER_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define ENCODER_QUEUE_LENGTH                    ( 1 )

void encoder_sensor_create (void){
	 encoder.eQueue = xQueueCreate( 32, sizeof(float));
}

void encoder_sensor_send(float L, float R){
    struct encoder_message *peMessage;
    eMessage.left  = L;
	eMessage.right = R;
    peMessage = &eMessage;
	xQueueSendToBackFromISR( encoder.eQueue, ( void * ) &peMessage, (BaseType_t) 0);
}

void calculate_encoder_val(void){
    encoder.TIME_TO_CALCULATE = false;
    encoder.float_1 = (float)DRV_TMR1_CounterValueGet()/180;
    encoder.float_2 = (float)DRV_TMR2_CounterValueGet()/180; // x/(20*.2) = 4
    encoder_sensor_send(encoder.float_1, encoder.float_2);
    DRV_TMR1_CounterClear();
    DRV_TMR2_CounterClear();
    }

struct encoder_message* encoder_sensor_receive(void){
    struct encoder_message *inMessage;
	if(xQueueReceive( encoder.eQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void initializeEncoder(void){
    encoder.TIME_TO_CALCULATE = false;
    encoder_sensor_create();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    encoder.rightVal = 0;
    encoder.leftVal = 0;
}
uint8_t i = 0;
void ENCODER(void){
    initializeEncoder();
    struct encoder_message *ENCODER_MESSAGE;
    
    for(;;){
        if(encoder.TIME_TO_CALCULATE){
            calculate_encoder_val();
        }
        if(uxQueueMessagesWaiting( encoder.eQueue ) > 0){
            ENCODER_MESSAGE = encoder_sensor_receive();
            encoder.rightVal = ENCODER_MESSAGE->right;
            encoder.leftVal = ENCODER_MESSAGE->left;
        }
        dbgOutputVal((uint32_t)(encoder.rightVal*100));
    }
}
/*******************************************************************************
 End of File
 */