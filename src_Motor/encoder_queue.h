#include "FreeRTOS.h"
#include "queue.h"
typedef enum
{
	/* Application's state machine's initial state. */
	SENSOR_QUEUE_STATE_INIT=0,

	/* TODO: Define states used by the application state machine. */

} SENSOR_QUEUE_STATES;

typedef struct
{
    /* The application's current state */
    SENSOR_QUEUE_STATES state;

    /* TODO: Define any additional data used by the application. */

    volatile uint32_t left20Count;
    volatile uint32_t right20Count;
    volatile float left20Countf;
    volatile float right20Countf;
} SENSOR_QUEUE_DATA;

SENSOR_QUEUE_DATA sensor;

struct encoder_message
    {
        uint32_t left;
		uint32_t right;
    } eMessage;

float Val1;
float Val2;

//void sensorq_create( void );
void encoder_sensorq_create( void );
//void encoder_sensorq_send(uint32_t L, uint32_t R);
void encoder_sensorq_send(float L, float R); 
void calculate_encoder_val(void);
struct encoder_message * encoder_sensor_receive( void );