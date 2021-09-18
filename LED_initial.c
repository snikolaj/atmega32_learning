#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/fuse.h>

void main(void){
  DDRA = 1; // set first pin in PORTA as output, all others are input
  
  PORTA = 0xFF // set all pins as output high (if the pins are inputs, pull up resistors will be enabled)
  while(1){
        if((PINA >> 1) & 1){ // if the second pin of port A is high, set the first pin high
            PORTA |= (1 << 0);
        }else{ // else set it low
            PORTA &= ~(1 << 0);
        }
    }
}
