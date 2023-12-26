#include <avr/io.h>
#include <util/delay.h>

#define __AVR_ATmega328P__ 

#define LED 0
#define LED_DDR DDRD
#define LED_PORT PORTD

int main() {
  LED_DDR |= _BV(LED);
  while (1) {
    LED_PORT |= _BV(LED);
    _delay_ms(1000);
    LED_PORT &= ~_BV(LED);
    _delay_ms(1000);
  }
}
