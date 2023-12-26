#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define EIGTH_SPEED 250

#define TONE(step, delay) \
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
      BUZZ_PORT |= _BV(BUZZ); \
      _delay_us(step); \
      BUZZ_PORT &= ~_BV(BUZZ); \
      _delay_us(step); \
    }

#define C TONE(956, EIGTH_SPEED)
#define D TONE(852, EIGTH_SPEED)
#define E TONE(758, EIGTH_SPEED)
#define F TONE(716, EIGTH_SPEED)
#define G TONE(638, EIGTH_SPEED)
#define Gis TONE(602, EIGTH_SPEED)
#define A TONE(568, EIGTH_SPEED)
#define H TONE(506, EIGTH_SPEED)
#define C_HIGH TONE(478, EIGTH_SPEED)

#define PAUSE _delay_ms(EIGTH_SPEED);
#define SHORT_PAUSE _delay_ms(EIGTH_SPEED / 12);

// definiuje cwiercnuty tzn 2 razy osemka
#define C2 C C
#define D2 D D
#define E2 E E
#define F2 F F
#define G2 G G
#define Gis2 Gis Gis
#define A2 A A
#define H2 H H
#define C2_HIGH C_HIGH C_HIGH
#define PAUSE2 PAUSE PAUSE

void zagraj_sto_lat(){
  PAUSE
  G2 E2 G2 E2 G2 A G F E F2 
  PAUSE2
  F2 D2 F2 D2 F2 G F E D E2
  PAUSE2
  G SHORT_PAUSE G E2 G SHORT_PAUSE G E2 G2 C H A Gis A2
  PAUSE2
  H2 SHORT_PAUSE H2 SHORT_PAUSE H2 SHORT_PAUSE
  H PAUSE H PAUSE 
  C2_HIGH C2_HIGH C2_HIGH C2_HIGH

}

void zagraj_gama(){
  C
  E
  F
  G
  A
  H

}

int main() {
  BUZZ_DDR |= _BV(BUZZ);
  while (1) {
    zagraj_sto_lat();
  }
}