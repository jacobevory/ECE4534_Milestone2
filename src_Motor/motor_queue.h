#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>

typedef struct
{
    QueueHandle_t mQueue;
    bool dirL;
    bool dirR;
    uint32_t spdL;
    uint32_t spdR;
} MOTOR_QUEUE_DATA;

MOTOR_QUEUE_DATA motorQ;

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
void initializeMotorQueue(void);