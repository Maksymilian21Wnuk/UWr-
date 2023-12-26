#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#define RED PB3
#define GREEN PB2
#define BLUE PB1

#define LED_DDR DDRB
#define LED_PORT PORTB

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM11  = 1110 -- fast PWM top=ICR1
  // CS10   = 101  -- prescaler 0
  // ICR1  = 1023
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB = _BV(GREEN) | _BV(BLUE) | _BV(RED);
}


const uint16_t brightness[] = {0, 1, 2, 4, 8, 16, 32, 48, 64, 96, 128, 196, 256, 386, 512, 768, 1023};
const uint16_t size = sizeof(brightness) / sizeof(uint16_t);

int main(){ 
    LED_PORT = _BV(RED) | _BV(GREEN) | _BV(BLUE);

    timer1_init();

    while(1){
        for (uint16_t i = 0; i < size; i++){
            OCR1A = brightness[i];
            _delay_ms(100);
        }

        for (int16_t i = size; i > -1; i--){
            OCR1A = brightness[i];
            _delay_ms(100);
        }

    }

}