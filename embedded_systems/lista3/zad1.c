#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

// duration in ms 8th notes !!!
#define DURATION 250

// eight notes frequency for tone, calculated with formula:
// 1_000_000 / (2 * note_freq) 1 sekunda w 1000000us
#define C  956
#define D  852
#define E  758
#define F  716
#define G  638
#define Gis  602 
#define A  568
#define H  506
#define C_HIGH 478
#define P 0
#define SP 1

static const uint16_t sto_lat[] PROGMEM = {
  G, E, G, E, G, A, G, F, E, F, 
  P,
  F, D, F, D, F, G, F, E, D, E,
  P,
  G, SP, G, E, G, SP, G, E, G, C, H, A, Gis, A,
  P,
  H, SP, H, SP, H, SP,
  H, SP, H, SP,
  C_HIGH,
  /*
  P, P,
  G, SP, E, SP, E, SP, F, SP, D, D, SP,
  C, E, SP, G, SP,G, SP, E, SP, E, SP,
  F, SP, D, SP, D, SP, C, E, C, SP,
  C, SP, E, SP, E, SP, D, SP, F, SP,F, SP,
  C, E, SP, G, SP, G, SP, E, SP, E, SP,
  P, P
*/
  P, P
};

static const uint16_t sto_lat_duration[] PROGMEM = {
  2, 2, 2, 2, 2, 1, 1, 1, 1, 2,
  2,
  2, 2, 2, 2, 2, 1, 1, 1, 1, 2,
  2,
  1, 0, 1, 2, 1, 0, 1, 2, 2, 1, 1, 1, 1, 2,
  2,
  2, 0, 2, 0, 2, 0,
  1, 1, 1, 1,
  8,
  // wlazl kotek
  /*
  2, 2,
  2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0,
  2, 2, 0, 4, 0, 2, 0, 2, 0, 2, 0,
  2, 0, 2, 0, 2, 0, 2, 2, 4, 0,
  2, 0, 2, 0, 2, 0, 2, 0, 2, 0,
  2, 2, 0, 4, 0, 2, 0, 2, 0, 2, 0,
  2, 2*/
  2, 2
};


#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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
  return UDR0;
}

void tone_play(uint16_t step, uint16_t delay){
    delay = delay * DURATION;
    uint16_t temp;
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { 
        BUZZ_PORT |= _BV(BUZZ);
        temp = step;
        while (temp--){
            _delay_us(1);
        }
        BUZZ_PORT &= ~_BV(BUZZ); 
        temp = step;
        while (temp--){
            _delay_us(1); 
        } 


      }
}

FILE uart_file;

int main(){
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    BUZZ_DDR |= _BV(BUZZ);
    
    while (1)
    {
        for (int i = 0; i < sizeof(sto_lat) / sizeof(uint16_t); i++){
            uint16_t delay = pgm_read_word(&sto_lat_duration[i]);
            uint16_t freq = pgm_read_word(&sto_lat[i]);
            
            // short pause case
            if (freq == SP){
                _delay_ms(DURATION / 12);
            }
            // pause case
            else if (freq == P){
                for (int i = 0; i < delay; i++){
                    _delay_ms(DURATION);
                }

            }
            else{
              tone_play(freq, delay);
        }
        }
    }
    
}