/*
Lista 10 Zadanie 2
330572
Maksymilian Wnuk
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define SPEED 225 // how fast we want progress bar to be
#define ROW1 0x40

uint8_t pos=0;

int hd44780_transmit(char data, FILE *stream){
  LCD_WriteData(data);
  return 0;
}

FILE hd44780_file;

int main(){
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  // patterns for columns of glowing led
  uint8_t patterns[5] = {0b10000, 0b11000, 0b11100, 0b11110, 0b11111};


    for(uint8_t i = 0; i < 5; i++)
    {
        LCD_WriteCommand(HD44780_CGRAM_SET | (i<<3));
        // let every row be glowing
        for(uint8_t j=0;j<8;j++){
            LCD_WriteData(patterns[i]);
        }
    }
    while(1)
    {

      for(uint8_t i = 0; i < 16; i++)
      {
          for(uint8_t j = 0; j < 5; j++)
          {
              LCD_GoTo(0, 0);
              printf("Progress: %"PRIu8"%%", ((i * 5 + j + 1) * 100) / 80);
              LCD_GoTo(i, 1);
              printf("%c",j);
              _delay_ms(SPEED);
          }
        }
        LCD_GoTo(0, 0);
        printf("Completed 100%% ");
        _delay_ms(1000);
        LCD_Clear();
    }
}