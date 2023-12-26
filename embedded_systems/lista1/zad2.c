#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR DDRD
#define LED_PORT PORTD


int main(){    
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    LED_DDR |= 0xff;
    uint8_t blink = 0b10000000;
    LED_PORT = 0b0;
    while(1){
        for (int8_t i = 0; i < 7; i++){
            LED_PORT &= 0b0;
            LED_PORT |= blink;
            _delay_ms(200);
            blink >>= 1;
        }   
        for (int8_t i = 6; i >= 0; i-- ){
            LED_PORT &= 0b0;
            LED_PORT |= blink;
            _delay_ms(200);
            blink <<= 1;
        }
    
    }

}