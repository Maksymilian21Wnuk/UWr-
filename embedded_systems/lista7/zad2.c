/*
Wnuk Maksymilian
330572
Lista 7 zadanie 2

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

#define RECORD_TYPE "00"

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

// check if strings are equal, more convenient
inline uint8_t equal(char *s1, char *s2){
    return !strcmp(s1, s2);
}

// read bytes_count bytes starting at addr
inline void perform_read(uint16_t addr, uint16_t bytes_count, uint8_t *checksum){
    uint8_t val;
    i2cStart();
    // send write bit
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
    // set address
    i2cSend(addr & 0xff);
    // second start
    i2cStart();    
    while (bytes_count > 0){
        // send request for data
        i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
        val = i2cReadNoAck();
        *checksum += val;
        printf("%02x", val);
        bytes_count--;
        i2cStart();    
    }
    i2cStop();
}

// perform write on bytes_count bytes on addr 
inline void perform_write(uint16_t addr, uint16_t bytes_count){
    uint8_t val;
    // start i2c write
    i2cStart();
    // write request
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
    i2cSend(addr & 0xff);

    // write in one "transaction"
    while (bytes_count > 0){
        printf("Bytes:\n\r");
        scanf("%"SCNx8, &val);
        //printf("%"PRIx16"\n\r", val);
        i2cSend(val);
        bytes_count--;
    }
    i2cStop();
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
  uint16_t bytes_count = 1;
  uint8_t checksum = 0;
  char instruction[8] = {0};

  while(1) {
    scanf("%s", instruction);

    if (equal("read", instruction)){
        printf("\n\rRead\n\rType in addres and bytes count: \n\r");
        scanf("%"SCNx16 " %"SCNx16, &addr, &bytes_count);

        // print in i8hex start code byte count and address
        // %0nx at least n characters ( for zeroes )
        printf(":%02x%04x"RECORD_TYPE, bytes_count, addr);

        checksum += (bytes_count & 0xff) + (addr & 0xff);

        // start i2c read
        perform_read(addr, bytes_count, &checksum);

        // calculate 2's complimentary
        checksum = (uint8_t)(0x100 - (uint16_t)checksum);
        printf("%02x\n\r", checksum);

        checksum = 0;
    }

    else if (equal("write", instruction)){
        printf("\n\rWrite\n\rWriting, write each line in I8HEX: \r\n");
        printf("Byte count in hex: \n\r");
        scanf("%"SCNx16, &bytes_count);

        printf("Address in hex:\n\r");
        scanf("%"SCNx16, &addr);

        // no record type, no checksum
        perform_write(addr, bytes_count);
        printf("Wrote %"PRId16" bytes at %"PRIx16 "\n\r", bytes_count, addr);

    }
  }
}

