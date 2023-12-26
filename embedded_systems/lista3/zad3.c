#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD

#define LED_ON LED_PORT |= _BV(LED);
#define LED_OFF LED_PORT &= ~_BV(LED);

#define BLINK_AMOUNT 6
static uint16_t pot_tab[] = {50, 100, 150, 200, 250, 1023};
static uint16_t on_tab[] = {1, 2, 4, 7, 8, 8};
static uint16_t off_tab[] = {8, 12, 8, 5, 2, 1};

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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


FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();

  LED_DDR |= _BV(LED);

  LED_OFF

  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023);

    printf("%"PRIu16"\r\n", v);

  LED_ON

  if(v == 0) LED_PORT = 0;
  else if(v < 64) 
  {
    _delay_ms(1);
    LED_PORT = 0;
    _delay_ms(8);
  }
  else if(v < 128)
  {
      _delay_ms(2);
      LED_PORT = 0;
      _delay_ms(8);
  }
  else if(v < 256)
  {
      _delay_ms(4);
      LED_PORT = 0;
      _delay_ms(8);
  }
  else if(v < 512)
  {
      _delay_ms(7);
      LED_PORT = 0;
      _delay_ms(5);
  }
  else if(v < 800)
  {
      _delay_ms(8);
      LED_PORT = 0;
      _delay_ms(2);
  }
  else 
  {
    _delay_ms(8);
      LED_PORT = 0;
      _delay_ms(1);
      
  }

}
}

