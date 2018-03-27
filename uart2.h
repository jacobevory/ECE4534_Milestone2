#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>
#include "system_definitions.h"
#include "debug.h"

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
char uart_receive(void);
char uart_receive_from_transmit_queue(void);
void uart_send_to_receive_queue(char data);
void initializeUART(void);
void transmitUARTstring(char *string);
void transmitUARTchar(char);
void sendMotor(int seq);
void sendCol(int seq);
void sendLine(int seq);
void sendDist(int seq);
void sendReq(int seq);
void UART_Tasks(void);
void jsmnParse();