/*
Lista 9 zadanie 1
330572
Maksymilian Wnuk
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB


#define BTN PA7
#define BTN_PIN PINA
#define BTN_PORT PORTA

#define TIME_DELAY 10

static uint8_t circ_buffer[100]; // 100 * 10 ms

volatile static uint16_t val = 0;


void timer_init(){
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS01) | _BV(CS00); // prescaler: 64 1ms do 255
  
  OCR0A = 156;
  
  TIMSK0 = _BV(OCIE0A);           // enable interrupt on compare
}

ISR(TIM0_COMPA_vect){
  //LED_PORT |= _BV(LED);
  //_delay_ms(10);
  //LED_PORT &= ~_BV(LED);
  //_delay_ms(20);

  if(val >= 200)
    val -= 200;

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

  BTN_PORT |= _BV(BTN);

  timer_init();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();

  while(1){
    sleep_mode();
  }

}