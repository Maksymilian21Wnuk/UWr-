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


  uint8_t patterns[5] = {0b10000, 0b11000, 0b11100, 0b11110, 0b11111};

  uint8_t loc = 1;
  LCD_WriteCommand(0x40 + (loc * 8));
  for (int i = 0; i < 8; i++){
    LCD_WriteData(patterns[i]);
  }
  

  _delay_ms(1000);

  uint8_t progress = 0;
  uint8_t temp;
  while(1) {
    if(progress == 81){
      LCD_GoTo(0,0);
      printf("Completed      ");
      _delay_ms(1000);
      progress = 0;
    }
    LCD_Clear();
    LCD_GoTo(0,0);
    printf("Progress :%"PRIu8, progress);
    temp = progress;
    LCD_GoTo(0,1);
    while(temp >= 5){
      LCD_WriteData(5);
      temp -= 5;
    }
    LCD_WriteData(temp);
    _delay_ms(SPEED);
    progress++;
  }
}