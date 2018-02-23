#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>
#include "system_definitions.h"

typedef struct
{
    QueueHandle_t utQueue;
    QueueHandle_t urQueue;
    char transmit_char;
    char receive_char;
    
} UART_DATA;

UART_DATA uart;

struct uart_message
    {
    char data;
    } uMessage;


void uart_transmit_create(void);
void uart_send(char data);
void uart_receive(char data);
struct uart_message * uart_receive_from_transmit_queue(void);
struct uart_message * uart_receive_from_receive_queue(void);
void initializeUART(void);
void transmitUARTstring(const char *string);
void transmitUARTchar(char);
void UART(void);