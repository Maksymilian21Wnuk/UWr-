/*
Wnuk Maksymilian
330572
Lista 7 zadanie 1

*/

#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define DBG printf("asdf");

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

const uint8_t eeprom_addr = 0xa0;

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
  char instruction[8] = {0};

  while(1) {
    scanf("%s", instruction);

    if (equal("read", instruction)){
        printf("\n\rRead\n\rType in addres: \n\r");
        scanf("%"SCNx16, &addr);
        // start i2c read
        i2cStart();
        // send write bit
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        // set address
        i2cSend(addr & 0xff);
        // second start
        i2cStart();
        // send request for data
        i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
        val = i2cReadNoAck();
        i2cStop();
        printf("\n\r%"PRIx8"\n\r", val);
    }

    else if (equal("write", instruction)){
        printf("\n\rWrite\n\rType in addr and value: \r\n");
        scanf("%" SCNx16 " %"SCNx8, &addr, &val);
        // start i2c write
        i2cStart();
        // write request
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        i2cSend(addr & 0xff);
        i2cSend(val);
        i2cStop();
        printf("Wrote %"PRIx8" to %"PRIx16 "\n\r", val, addr);

    }
  }
}

