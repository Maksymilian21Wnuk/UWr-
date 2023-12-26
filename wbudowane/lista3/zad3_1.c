#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>


#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD



// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void pwm_init() {
    // Set Fast PWM mode with non-inverted output
    TCCR0A = _BV(WGM01) | _BV(WGM00) | _BV(COM0A1);
    TCCR0B = _BV(CS00); // No prescaler (full clock speed)
    DDRD |= _BV(PD5);   // PD6/OC0A as an output
}

int main()
{
  // zainicjalizuj ADC
  adc_init();
  LED_DDR |= _BV(LED);
  // mierz napięcie
  uint16_t p = (1 << 15);
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023);

    OCR0A = v;
    _delay_ms(10);
  }
}

