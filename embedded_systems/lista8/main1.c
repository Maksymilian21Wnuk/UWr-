/*
Lista 8 zadanie 1
Maksymilian Wnuk
330572
*/

/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/
#define __AVR_ATmega328P__ 

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/


#define LED_DDR DDRD
#define LED_PORT PORTD

#define LED_DDRC DDRC
#define LED_PORTC PORTC
#define LED PC0

#define BTN PB5
#define BTN_PIN PINB
#define BTN_PORT PORTB


/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static uint8_t circ_buffer[100] = {0};

static void vBlinkStrip(void* pvParameters);

static void vButtonBlinker(void* pvParameters);

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
int main(void)
{
    // Create task.
    xTaskHandle blink_strip_handle;
    xTaskHandle btn_blink_handle;

    xTaskCreate
        (
         vBlinkStrip,
         "blink_strip",
         configMINIMAL_STACK_SIZE + 32,
         NULL,
         1,
         &blink_strip_handle
        );

    xTaskCreate
        (
         vButtonBlinker,
         "blink_button_delay",
         configMINIMAL_STACK_SIZE + 32,
         NULL,
         1,
         &btn_blink_handle
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
static void vBlinkStrip(void* pvParameters)
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    LED_DDR |= 0xff;
    uint8_t blink = 0b10000000;
    LED_PORT = 0b0;
    for (;;){
        for (int8_t i = 0; i < 7; i++){
            LED_PORT &= 0b0;
            LED_PORT |= blink;
            vTaskDelay(200 / portTICK_PERIOD_MS);
            blink >>= 1;
        }   
        for (int8_t i = 6; i >= 0; i-- ){
            LED_PORT &= 0b0;
            LED_PORT |= blink;
            vTaskDelay(200 / portTICK_PERIOD_MS);
            blink <<= 1;
        }
    
    }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vButtonBlinker(void* pvParameters)
{

    LED_DDRC |= _BV(LED);    
    BTN_PIN &= ~_BV(PB5);
    while (1){
        for (int i = 0; i < 100; i++){
            // turn led on and change circ_buff to 0, because already changed          
            if (circ_buffer[i]){
                LED_PORTC = _BV(BTN);    
                circ_buffer[i] = 0;
            }
            // turn on in buffer
            if (!(BTN_PIN & _BV(PB5))){
                circ_buffer[i] = 1; 
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
            LED_PORTC = ~_BV(BTN);
        }

    }

}
