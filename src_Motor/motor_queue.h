#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>

typedef struct
{
    QueueHandle_t mQueue;
    bool s1,  s2,  s3,  s4,  s5,  s6,  s7;
} MOTOR_QUEUE_DATA;

MOTOR_QUEUE_DATA motor;

struct motor_message
    {
        bool DL;
        bool DR;
        uint32_t SL;
        uint32_t SR;
    } mMessage;


void motor_create(void);
void motor_send(bool DL, bool DR, uint32_t SL, uint32_t SR);
struct motor_message * motor_receive( void );
void initializeMotor(void);
void MOTOR_QUEUE(void);