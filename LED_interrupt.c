#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/fuse.h>

ISR(INT2_vect){
    PORTA ^= 1; // toggle first pin
}

void main(void) {
    DDRA = 1; // set first A pin as outputs
    DDRB = 0; // set all pins as inputs
    
    //SREG |= (1 << 7); // enable global interrupts
    GICR |= (1 << 5); // enable INT2 (PB3), falling edge enabled by default
    sei(); // interrupt enable (does the same thing as SREG |= (1 << 7)
    
    PORTA = 0xFF; // set all pins as output high (if input they will be pulled up)
    while(1){
    }
}
