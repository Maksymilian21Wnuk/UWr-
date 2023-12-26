#define __AVR_ATmega328P__ 

#include <avr/io.h>
//#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

volatile float res = 0;

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

void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC 
  ADCSRA |= _BV(ADATE) | _BV(ADIE); // auto conversion trigger enable & adc interrupt enable
  ADCSRB |= _BV(ADTS1);   // external interrupt req 0
}

void io_init()
{
  // ustaw pull-up na PD2 INT0
  PORTD |= _BV(PORTD2);
  // ustaw wyzwalanie przerwania na INT0 zboczem narastajacym
  EICRA |= _BV(ISC00) | _BV(ISC01);
  // odmaskuj przerwania dla INT0 i INT1
  EIMSK |= _BV(INT0);
}

ISR(INT0_vect){}

ISR(ADC_vect){
  // zablokuj przerwania
  EIMSK &= ~_BV(INT0);
  uint16_t value = ADC;
  float u = (5.0 / 1023.0) * value; // 5 v ref 10bits
  res = u;
  // odblokuj przerwania
  EIMSK |= _BV(INT0); 
  //printf("asdf");
}



FILE uart_file;

int main(){
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    io_init();
    adc_init();
    sei();

    while(1){
      printf("Photoresistor value: %f\n\r", res);
      _delay_ms(1000);
    }


}