/*  Lista 4 Zadanie 2
    Wnuk Maksymilian 
    330572
*/

#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
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

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}


// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC 
}

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A1  -- non-inverting mode
  // WGM11 WGM12 WGM 13  = 1110 -- fast PWM top=ICR1
  // CS10   = 101  -- prescaler 1
  // ICR1  = 1024
  ICR1 = 1024;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}



FILE uart_file;

const uint16_t brightness[] = {1024, 512, 256, 128, 64, 32, 8, 4, 2, 1, 0};

int main(){

  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  adc_init();
  timer1_init();

  OCR0A = 0;

  while(1){
    ADCSRA |= _BV(ADSC);
    while (!(ADCSRA & _BV(ADIF)));  
    ADCSRA |= _BV(ADIF);
    uint16_t res = (ADC / 10) - 1;
    if (res > 8){
      res = 10;
    }
    printf("res: %"PRIu16"\n\r", res);

    OCR1A = brightness[res];

  }
}