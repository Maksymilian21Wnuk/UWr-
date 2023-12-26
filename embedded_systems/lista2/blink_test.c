#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>


#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main() {
  LED_DDR |= _BV(LED);
  LED_PORT &= ~_BV(LED);
  while (1) {
    if (BTN_PIN)
      LED_PORT = _BV(LED);
    else
      LED_PORT = ~_BV(LED);
  }
}

