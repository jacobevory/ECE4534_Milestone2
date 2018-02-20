

#include "motor_queue.h"


#define MOTOR_QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define MOTOR_QUEUE_LENGTH                    ( 1 )

void motor_create (void){
	 motorQ.mQueue = xQueueCreate( 32, sizeof(uint32_t));
}

void motor_send(bool DL, bool DR, uint32_t SL, uint32_t SR){
    struct motor_message *pmMessage;
    mMessage.DL = DL;
    mMessage.DR = DR;
    mMessage.SL = SL;
    mMessage.SR = SR;
    pmMessage = &mMessage;
	xQueueSendToBack( motorQ.mQueue, ( void * ) &pmMessage, (BaseType_t) 0);
}

struct motor_message* motor_receive(void){
    struct motor_message *inMessage;
	if(xQueueReceive( motorQ.mQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void initializeMotorQueue(void){
    motor_create();
}

/*
void MOTOR_QUEUE(void){
    initializeMotorQueue();
    struct motor_message *MOTOR_MESSAGE;
    
    for(;;){
        if(uxQueueMessagesWaiting( motorQ.mQueue ) > 0){
            MOTOR_MESSAGE = motor_receive();
        }
    }
}*/
/*******************************************************************************
 End of File
 */