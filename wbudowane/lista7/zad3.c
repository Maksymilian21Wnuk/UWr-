#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define DBG printf("asdf");

#define READ 0b11010001
#define WRITE 0b11010000

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

const uint8_t clock_addr = 0x68;

#define i2cCheck(code, msg) \
if ((TWSR & 0xf8) != (code)) { \
    printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
    i2cReset(); \
    continue; \
}

inline uint8_t equal(char *s1, char *s2){
    return !strcmp(s1, s2);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();
  // program testowy
  uint16_t addr = 0;
  uint8_t val = 0;
  char instruction[16] = {0};

  while(1) {
    scanf("%s", instruction);

    if (equal("date", instruction)){
        addr = 0x04;
        i2cStart();
        // send write bit
        i2cSend(WRITE);
        // set address
        i2cSend(addr & 0xff);
        // send request for data
        i2cSend(READ);
        val = i2cReadNoAck();
        i2cStop();
        printf("Current date: %"PRIx8"\n\r", val & 0x0f);
    }

    else if (equal("time", instruction)){
        addr = 0x00;
        i2cStart();
        // send write bit
        i2cSend(WRITE);
        // set address
        i2cSend(addr & 0xff);
        // send request for data
        i2cSend(READ);
        val = i2cReadNoAck();
        i2cStop();
        printf("Current seconds: %"PRIx8"\n\r", val);
    }

    else if (equal("set", instruction)){
        printf("\n\r");
        scanf("%s %"SCNu8"\n", instruction, &val);
        if (equal("time", instruction)){
            addr = 0x00;
            i2cStart();
            // write request
            i2cSend(WRITE);
            i2cSend(addr & 0xff);
            i2cSend(val);
            i2cStop();

        }
        else if(equal("date", instruction)){
            addr = 0x04;
            i2cStart();
            // write request
            i2cSend(WRITE);
            i2cSend(addr & 0xff);
            i2cSend(val);
            i2cStop();
        }
    }

  }
}
