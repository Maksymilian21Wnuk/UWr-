/*
lista 6 zadanie 4
Maksymilian Wnuk
*/

#define __AVR_ATmega328P__ 
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define PRESCALER 1024
#define OCR_VAL (F_CPU / (2 * PRESCALER) - 1) * 2

volatile uint8_t num = 0;

const uint8_t numbers[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// init timer for counting 1 s
void timer_init(){
  TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12); // prescaler: 1024 update at ocr1a
  TIMSK1 = _BV(OCIE1A);           // enable interrupt on compare

  OCR1A = OCR_VAL;
}



// inicjalizacja SPI
void spi_init()
{
    // ustaw piny MOSI, SCK i ~SS jako wyjścia
    DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2);
    // włącz SPI w trybie master z zegarem 250 kHz
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// transfer jednego bajtu
void spi_transfer(uint8_t data)
{
    PORTB |= _BV(PB1);
    
    // rozpocznij transmisję
    SPDR = data;
    
    // czekaj na ukończenie transmisji
    while (!(SPSR & _BV(SPIF)));
    
    // wyczyść flagę przerwania
    SPSR |= _BV(SPIF);
    
    // koniec ladowania led
    PORTB &= ~_BV(PB1);    
}

ISR(TIMER1_COMPA_vect){
    if (num >= 10){
        num = 0;
    }

    spi_transfer(numbers[num++]);
}


int main(){
    // init spi
    spi_init();
    timer_init();
    // init output LA OE
    DDRB |= _BV(PB1) | _BV(PB2);
    uint8_t i = 0;
    PORTB |= _BV(PB1);
    // turn leds on OE pin
    PORTB &= ~_BV(PB2);
    
    sei();
    set_sleep_mode(SLEEP_MODE_IDLE);

    while(1){
        sleep_mode();
    }

}