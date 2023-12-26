/*
Lista 10 Zadanie 1
330572
Maksymilian Wnuk
*/


#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define CURSOR '|'  // cursor icon
#define START 1     // start of screen
#define ENDL '\r'  // dont know why, but carriage return is endl

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}


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
  // some modification for echoing while in scanf
  char received = UDR0;
  uart_transmit(received, stream);
  return received;
}

FILE uart_file;
FILE hd44780_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = &uart_file;

  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;
  // program testowy
  
  char inp;

  // position of cursor
  uint8_t pos = START;
  uint8_t level = 0;
  // buffer for string 
  char strbuf[16] = {'\0'}; 
  uint8_t buf_len = 0;
  while(1) {
    printf("%c", CURSOR);
    LCD_GoTo(pos - 1, level);
    scanf("%c", &inp);
    
    if (inp == ENDL || pos > 16){
      // change level for 1
      level = 1;
      // clear and print buffer
      LCD_Clear();
      LCD_GoTo(0, 0);
      printf("%s", strbuf);
      // change buf_len to 0
      buf_len = 0;
      for (uint8_t i = 0; i < 16; i++){
        strbuf[i] = '\0';
      }
      LCD_GoTo(0, 1);
      pos = START;
    }

    else{
      *(strbuf + buf_len) = inp;
      printf("%c", inp);
      buf_len++;
      pos++;
    }
  }
}

