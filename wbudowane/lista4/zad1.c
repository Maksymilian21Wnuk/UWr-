/*  Lista 4 Zadanie 1
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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}
FILE uart_file;



int main(){
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer1_init();

  uint16_t t1, t2, t3, t4;

  volatile uint8_t a1, aa1;
  
  TCNT1 = 0;
  a1 += aa1;
  t1 = TCNT1;

  TCNT1 = 0;
  a1 -= aa1;
  t2 = TCNT1;

  TCNT1 = 0;
  a1 /= aa1;
  t3 = TCNT1;

  TCNT1 = 0;
  a1 *= aa1;
  t4 = TCNT1;

  printf("Czas w cyklach uint8_t: \r\n+ %"PRIu16" \r\n- %"PRIu16" \r\n/ %"PRIu16" \r\n* %"PRIu16"\n\r", t1,t2,t3,t4);

  volatile uint16_t a2, aa2;
  
  TCNT1 = 0;
  a2 += aa2;
  t1 = TCNT1;

  TCNT1 = 0;
  a2 -= aa2;
  t2 = TCNT1;
    
  TCNT1 = 0;
  a2 /= aa2;
  t3 = TCNT1;

  TCNT1 = 0;
  a2 *= aa2;
  t4 = TCNT1;

  printf("Czas w cyklach uint16_t: \r\n+ %"PRIu16" \r\n- %"PRIu16" \r\n/ %"PRIu16" \r\n* %"PRIu16"\n\r", t1,t2,t3,t4);

  volatile uint32_t a3, aa3;
  
  TCNT1 = 0;
  a3 += aa3;
  t1 = TCNT1;

  TCNT1 = 0;
  a3 -= aa3;
  t2 = TCNT1;
    
  TCNT1 = 0;
  a3 /= aa3;
  t3 = TCNT1;

  TCNT1 = 0;
  a3 *= aa3;
  t4 = TCNT1;

  printf("Czas w cyklach uint32_t: \r\n+ %"PRIu16" \r\n- %"PRIu16" \r\n/ %"PRIu16" \r\n* %"PRIu16"\n\r", t1,t2,t3,t4);

  volatile uint64_t a4, aa4;
  
  TCNT1 = 0;
  a4 += aa4;
  t1 = TCNT1;

  TCNT1 = 0;
  a4 -= aa4;
  t2 = TCNT1;
    
  TCNT1 = 0;
  a4 /= aa4;
  t3 = TCNT1;

  TCNT1 = 0;
  a4 *= aa4;
  t4 = TCNT1;

  printf("Czas w cyklach uint64_t: \r\n+ %"PRIu16" \r\n- %"PRIu16" \r\n/ %"PRIu16" \r\n* %"PRIu16"\n\r", t1,t2,t3,t4);

  volatile float a5, aa5;

  TCNT1 = 0;
  a5 += aa5;
  t1 = TCNT1;

  TCNT1 = 0;
  a5 -= aa5;
  t2 = TCNT1;
    
  TCNT1 = 0;
  a5 /= aa5;
  t3 = TCNT1;

  TCNT1 = 0;
  a5 *= aa5;
  t4 = TCNT1;

  printf("Czas w cyklach float: \r\n+ %"PRIu16" \r\n- %"PRIu16" \r\n/ %"PRIu16" \r\n* %"PRIu16"\n\r", t1,t2,t3,t4);

}