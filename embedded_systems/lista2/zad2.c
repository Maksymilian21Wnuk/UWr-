#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define TIME_DELAY 10


// buffer for storing state of button
static uint8_t buffer[100];

// array for storing morse codes, basically from list 1
const uint8_t morse_arr[] = {
  0b01000010,  // a
  0b10000001,  // b 
  0b10000101,   // c
  0b01100001,   //d
  0b00100000,   //e
  0b10000100,   //f 
  0b01100011,   //g
  0b10000000,   // h
  0b01000000,
  0b10001000,   //j
  0b01100101,
  0b10000010,   //l
  0b01000011,
  0b01000001, //n
  0b01100111, //o
  0b10000110, // p
  0b10001011,
  0b01100010,  // r
  0b01100000,
  0b00100001,
  0b01100100, // u
  0b10001000, // v
  0b01100110,
  0b10001001, // x
  0b10001101,
  0b10000011  //z
};

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

FILE uart_file;


// find morse code with given num
// in morse array
void find(uint8_t num){
  for (int i = 0; i < 26; i++){
    if (morse_arr[i] == num){
      printf("%c", i + 97);
    }
  }
}

void begin_listening(){
    // alert user of starting listening after 0.5 s
    LED_PORT = _BV(PD5);
    _delay_ms(500);
    LED_PORT = ~_BV(PD5);

    // listen for changes in button
    // time needed for turning on led
    // if time for dot exceeded 
    uint8_t time;
    for (int i = 0; i < 100; i++){
      if (BTN_PIN & _BV(BTN)){
        buffer[i] = 0;
        LED_PORT = ~_BV(LED);
        time = 0;

      }
      else{
        buffer[i] = 1;
        if (time >= 10){
          LED_PORT = _BV(LED);
        }
      }
      time += 1;
      _delay_ms(30);
    }
    /*
    for (int i = 0; i < 100; i++){
      printf("%" PRIu8, buffer[i]);
    }*/

    // look for changes of states
    int start = 0;
    uint8_t sums[6] = {0};
    // while not ones, find for first one
    while (!buffer[start]){
      start += 1;
    };

    // sum all ones which are button presses
    int which = 0;
    while (start < 100){
      while(buffer[start]){
        sums[which] += 1;
        start += 1;
      }
      // first zero encounter
      while (!buffer[start]){
        start += 1;
      }

      which += 1;      

      }
    // analyse the sums of changes the states
    // less than 10 changes in 3 seconds 30 ms intervals
    // means dot
    // more than 10 but less 90 dash and more than 90 means space
    int len = 0;
    uint8_t res = 0x00;
    for (int i = 0; i < 5; i++){
      if (sums[i] < 10 && sums[i]){
        res |= 0 << i;
        len++;
      }
      else if(sums[i] >= 10 && sums[i] < 90){
        res |= 1 << i;
        len++;
      }
      // if pressed through whole listening,
      // show that by turning led on and waiting 0.5 secs
      else if(sums[i] >= 90){
        LED_PORT = _BV(PD5);
        printf(" ");
        _delay_ms(500);
        LED_PORT = ~_BV(PD5);
      }
    }

    res |= (len << 5);

    find(res);
    LED_PORT = _BV(PD5);
    _delay_ms(100);
    LED_PORT = ~_BV(PD5);
    _delay_ms(100);
    LED_PORT = _BV(PD5);
    _delay_ms(100);
    LED_PORT = ~_BV(PD5);
}

int main(){
    LED_DDR |= _BV(LED);    
    BTN_PORT |= _BV(BTN);
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file; 

    while (1){
      // if turned on button begin listening to morse code
        if (!(BTN_PIN & _BV(BTN))){
            begin_listening();
        }

        _delay_ms(10);
    }

}