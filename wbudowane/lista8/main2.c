/*
Lista 8 Zadanie 2
Maksymilian Wnuk
330572
*/


/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/
#define __AVR_ATmega328P__ 

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <avr/io.h>


#include <stdio.h>

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define LED_DDRC DDRC
#define LED_PORTC PORTC
#define LED PC0

#define MAX_Q_LEN 10
#define Q_VAL_SIZE sizeof(uint16_t)

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/


static void vSender(void* pvParameters);

static void vReceiver(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);
void uart_init(void);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);

// inicjalizacja UART
void uart_init(void)
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

int uart_transmit(char c, FILE *stream) {
  while (!(UCSR0A & _BV(UDRE0))) taskYIELD();
  UDR0 = c;
  return 0;
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0))) taskYIELD();
  char c = UDR0;
  // echo
  uart_transmit(c, stream);
  return c;
}

QueueHandle_t Queue1;
uint8_t q_size = 0;

int main(void)
{
    // initialize uart
    uart_init();
    stdin = stdout = stderr = &uart_file;

    Queue1 = xQueueCreate(
        MAX_Q_LEN,  // 10
        Q_VAL_SIZE  // sizeof u16
    );

    // Create task.
    xTaskHandle uart_sender;
    xTaskHandle uart_receiver;

    xTaskCreate
        (
         vSender,
         "uart send blink ms",
         configMINIMAL_STACK_SIZE + 32,
         NULL,
         1,
         &uart_sender
        );

    xTaskCreate
        (
         vReceiver,
         "uart receive and blink ms",
         configMINIMAL_STACK_SIZE + 32,
         NULL,
         1,
         &uart_receiver
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSender(void* pvParameters)
{
    uint16_t delay; 
    for (;;){
        //printf("Enter ms value: \n\r");
        scanf("%"SCNu16, &delay);
        printf("Queue size: %"PRIu8" : 10\n\r", ++q_size);

        xQueueSendToBack(
            Queue1,
            (void *) &delay,
            (TickType_t)0);

        //vTaskDelay(10);
    }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vReceiver(void* pvParameters)
{
    LED_DDRC |= _BV(LED);
    for (;;){
        uint16_t delay;
        if (xQueueReceive(
                Queue1,
                (void *) &delay,
                (TickType_t)0) == pdPASS){
                    //printf("%"PRIu16"\n\r", delay);  
                    printf("Removal of %"PRIu16 ". Queue size: %"PRIu8 " : 10\n\r", delay ,--q_size);      
                    LED_PORTC |= _BV(LED);
                    vTaskDelay(delay / portTICK_PERIOD_MS);
                    LED_PORTC &= ~_BV(LED);
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }

    }
}
