/*
lista 6 zadanie 1
Maksymilian Wnuk
*/

#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PD5 
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PD2
#define BTN_PIN PIND
#define BTN_PORT PORTD

#define TIME_DELAY 10

static uint8_t circ_buffer[1000]; // 1000 * 1 ms

volatile uint16_t val = 0;


void timer_init(){
  //TCCR0A = "WGM0 1 2 = 0 immediate update at top 0xff = 255"
  TCCR0B = _BV(CS01) | _BV(CS00); // prescaler: 64 1ms do 255
  TIMSK0 = _BV(OCIE0A);           // enable interrupt on compare
}

ISR(TIMER0_COMPA_vect){
  if(val >= 1000)
    val -= 1000;

  if(circ_buffer[val])
    LED_PORT |= _BV(LED);
  else {
    LED_PORT &= ~_BV(LED);
  }
  if (!(BTN_PIN & _BV(BTN)) ){
    circ_buffer[val] = 1;
  } 
  else {
    circ_buffer[val] = 0;
  }
  val++;

}

int main(){
  LED_DDR = _BV(LED);
  LED_PORT &= ~_BV(LED);

  BTN_PIN |= _BV(BTN);

  timer_init();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();

  while(1){
    sleep_mode();
  }

}