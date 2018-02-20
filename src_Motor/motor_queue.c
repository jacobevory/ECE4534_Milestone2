

#include "motor_queue.h"


#define MOTOR_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define MOTOR_QUEUE_LENGTH                    ( 1 )

void motor_create (void){
	 motor.mQueue = xQueueCreate( 32, sizeof(uint32_t));
}

void motor_send(bool DL, bool DR, uint32_t SL, uint32_t SR){
    struct motor_message *pmMessage;
    pmMessage = &mMessage;
	xQueueSendToBackFromISR( motor.mQueue, ( void * ) &pmMessage, (BaseType_t) 0);
}

struct motor_message* motor_receive(void){
    struct motor_message *inMessage;
	if(xQueueReceive( motor.mQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void initializeMotorQueue(void){
    motor_create();
}

void MOTOR_QUEUE(void){
    initializeMotorQueue();
    struct motor_message *MOTOR_MESSAGE;
    
    for(;;){
        if(uxQueueMessagesWaiting( motor.mQueue ) > 0){
            MOTOR_MESSAGE = motor_receive();
        }
    }
}
/*******************************************************************************
 End of File
 */