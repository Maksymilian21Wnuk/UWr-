#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


#define LED 5
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define SPACE 1000
#define DOT 200
#define DASH 600

#define GET_LEN(x) x >> 5

FILE uart_file;

// char - 97 zwroci kod dla chara morse'a
// pierwsze 3 bity dlugosc okreslaja
const uint8_t morse_arr[] = {
  0b01000010,  // a
  0b10000001,  // b 
  0b10000101,   // c
  0b01100001,   //d
  0b00100000,   //e
  0b10000100,   //f 
  0b01100011,   //g
  0b10000000,   // h
  0b01000000,
  0b10001000,   //j
  0b01100101,
  0b10000010,   //l
  0b01000011,
  0b01000001, //n
  0b01100111, //o
  0b10000110, // p
  0b10001011,
  0b01100010,  // r
  0b01100000,
  0b00100001,
  0b01100100, // u
  0b10001000, // v
  0b01100110,
  0b10001001, // x
  0b10001101,
  0b10000011  //z
};

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
int uart_transmit(char data, FILE *stream){
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream){
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

void morse_blink(char c){
  if (c == ' '){
    LED_PORT = ~_BV(LED);
    _delay_ms(SPACE);  
  }
  else
  {
    uint8_t morse_value = morse_arr[c - 97];
    uint8_t len = GET_LEN(morse_value);
    for (uint8_t i = 0; i < len; i++){
      uint8_t temp = morse_value & 0b1;
      LED_PORT = _BV(LED);
      if (temp == 0b1){
        _delay_ms(DASH);
      }
      else{
        _delay_ms(DOT);
      }
      LED_PORT = ~_BV(LED);
      _delay_ms(200);
      morse_value >>= 1;
    }

  }
  LED_PORT = ~_BV(LED);
  _delay_ms(SPACE);
}


int main() {

  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  LED_DDR |= _BV(LED);

  char c = ' ';

  while(1){
    scanf("%c", &c);
    morse_blink(c);
  }

}
