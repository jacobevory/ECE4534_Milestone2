#include "FreeRTOS.h"
#include "queue.h"

typedef struct
{
    /* TODO: Define any additional data used by the application. */

    volatile uint32_t left20Count;
    volatile uint32_t right20Count;
    volatile float left20Countf;
    volatile float right20Countf;
} ENCODER_QUEUE_DATA;

ENCODER_QUEUE_DATA encoder;

struct encoder_message
    {
        float left;
		float right;
    } eMessage;

float Val1;
float Val2;

//void sensorq_create( void );
void encoder_sensor_create( void );
//void encoder_sensorq_send(uint32_t L, uint32_t R);
void encoder_sensor_send(float L, float R); 
void calculate_encoder_val(void);
struct encoder_message * encoder_sensor_receive( void );