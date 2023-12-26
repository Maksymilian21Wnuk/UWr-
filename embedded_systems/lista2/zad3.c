#define __AVR_ATmega328P__ 

#include <avr/io.h>
#include <util/delay.h>


#define BTN0 PB4
#define BTN1 PB3
#define BTN2 PB2
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define LED_DDR DDRD
#define LED_PORT PORTD

uint8_t gray_code(uint8_t n){
    return n ^ (n >> 1);
}


int main(){
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);    
    BTN_PORT |= 0xff;
    LED_DDR = 0xff;
    LED_PORT = 0;
    
    // n'th gray code
    uint8_t nth_code = 0;
    // debouncing used vars
    uint8_t pressed0, pressed1, pressed2;

    while(1){
        // if not pressed previously, change pressed0
        // to 1 to prevent from debouncing
        if (!(BTN_PIN & _BV(BTN0)) & !pressed0){
            nth_code = 0;
            pressed0 = 1;
        }
        // if pressed in previous 50ms, do nothing
        // and change pressed to 0
        else if(pressed0){
            pressed0 = 0;
        }
        if (!(BTN_PIN & _BV(BTN1)) & !pressed1){
            nth_code += 1;
            pressed1 = 1;
        }
        else if(pressed1){
            pressed1 = 0;
        }
        if (!(BTN_PIN & _BV(BTN2)) & !pressed2){
            nth_code -= 1;
            pressed2 = 1;
        }
        else if(pressed2){
            pressed2 = 0;
        }
        
        // set leds to n'th gray code
        LED_PORT = gray_code(nth_code);
        _delay_ms(100);
    }
}
