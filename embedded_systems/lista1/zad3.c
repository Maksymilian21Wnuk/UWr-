#define __AVR_ATmega328P__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

const uint8_t numbers[] = {
    0b10000010, // 0
    0b10110111, // 1
    0b11000001, // 2
    0b10010001, // 3
    0b10110100, // 4
    0b10011000, // 5
    0b10001000, // 6
    0b10110011, // 7
    0b10000000, // 8
    0b10010000, // 9
};

int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    LED_DDR |= 0xff;
    LED_PORT |= 0x00;
    LED_PORT ^= 0xff;
    while (1){
        for (int i = 0; i < 10; i++){
            LED_PORT = numbers[i];
            _delay_ms(1000);
        }

    }
}