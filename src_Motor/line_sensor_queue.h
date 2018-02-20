#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>

typedef struct
{
    QueueHandle_t lQueue;
    bool s1,  s2,  s3,  s4,  s5,  s6,  s7;
} LINE_QUEUE_DATA;

LINE_QUEUE_DATA line;

struct line_message
    {
        bool s1,  s2,  s3,  s4,  s5,  s6,  s7;
    } lMessage;


void line_sensor_create(void);
void line_sensor_send(bool s1, bool s2, bool s3, bool s4, bool s5, bool s6, bool s7);
struct line_message * line_sensor_receive( void );
void initializeLineSensor(void);
void LINE_SENSOR(void);