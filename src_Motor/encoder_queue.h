#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>

typedef struct
{
    QueueHandle_t eQueue;
    bool TIME_TO_CALCULATE;
    float float_1;
    float float_2;
    float rightVal;
    float leftVal;
} ENCODER_QUEUE_DATA;

ENCODER_QUEUE_DATA encoder;

struct encoder_message
    {
        float left;
		float right;
    } eMessage;


void encoder_sensor_create(void);
void encoder_sensor_send(float L, float R); 
void calculate_encoder_val(void);
struct encoder_message * encoder_sensor_receive( void );
void initializeEncoder(void);
void ENCODER(void);