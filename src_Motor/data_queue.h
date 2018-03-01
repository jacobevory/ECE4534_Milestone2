#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>

typedef struct
{
    QueueHandle_t dataQueue;
} DATA_QUEUE_DATA;

DATA_QUEUE_DATA data;

struct data_message
    {
        enum message_t { Encoder, Distance, Color, Line, Motor, Uart_receive, Uart_send, Rollover_error} messageType;
        float left;
		float right;
        uint32_t distance;
        enum color_t { red, green, blue, black } color;
        uint8_t line;
        uint16_t speed_left;
        uint16_t speed_right;
        bool direction_left;
        bool direction_right;
        char * uart;
    } dataMessage;


void data_queue_create(void);
void encoder_data_send(float L, float R); 
void distance_data_send(uint32_t d);
void color_data_send(int8_t c);
void line_data_send(uint8_t l);
void motor_data_send(uint32_t speed_left, uint32_t speed_right, bool direction_left, bool direction_right);
void uart_data_send_send(char * c);
void uart_data_receive_send(char * c);
void encoder_counter_rollover_error(void);
struct data_message * data_receive( void );
void initializeDataQueue(void);