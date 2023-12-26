#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <util/delay.h>


#define LED_DDRC DDRC
#define LED_PORTC PORTC
#define LED PC0

#define BTN PB5
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define TIME_DELAY 10

static uint8_t circ_buffer[100];


int main(){
    LED_DDRC |= _BV(LED);    
    BTN_PIN &= ~_BV(PB5);
    while (1){
        for (int i = 0; i < 100; i++){
            // turn led on and change circ_buff to 0, because already changed          
            if (circ_buffer[i]){
                LED_PORTC = _BV(BTN);    
                circ_buffer[i] = 0;
            }
            // turn on in buffer
            if (!(BTN_PIN & _BV(PB5))){
                circ_buffer[i] = 1; 
            }
            _delay_ms(10);
            LED_PORTC = ~_BV(BTN);
        }

    }

}