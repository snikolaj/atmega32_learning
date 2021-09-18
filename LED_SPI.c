#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/fuse.h>

uint8_t hAddr = 0;
uint8_t vAddr = 0;


/* ================== SETUP FUNCTIONS ================== */
void interruptsSetup(void){
    //SREG |= (1 << 7); // enable global interrupts
    GICR |= (1 << 5); // enable INT2, falling edge enabled by default
}

void SPIMasterInit(void){
    SPCR = 0b01010000; // set SPI enable and master select
}

void customSetup(void){
    // pin setup
    DDRA = 1; // set first A pin as outputs
    DDRB = 0b10111000; // set pins as needed, 1 is output and 0 is input
    PORTA = 0xFF; // set all pins as output high (if input they will be pulled up)
    
    // peripherals setup
    interruptsSetup();
    SPIMasterInit();
    
    sei(); // interrupt enable, interrupts are one-shot by default
}

/* ================== REGULAR FUNCTIONS ================== */

uint8_t SPITransceive(uint8_t data){
    SPDR = data; // send something
    while(!(SPSR & (1 << SPIF))); // wait for the something to be sent
    return SPDR; // return what the transceiver received
    // when writing to SPDR, it is writing to the register
    // when reading from SPDR, it is reading from the receive buffer
}

uint8_t PSRRead(){
    // using SN74HC165
    // connect SH/!LD to PB4
    // connect SCK to PB7 (SCK)
    // connect Qh to PB6 (MISO)
    // connect CLK INH to ground
    PORTB &= ~(1 << 3); // set PB4 low (load in shift register)
    PORTB |= (1 << 3); // set PB4 high (shift in shift register)
    return SPITransceive(0);
}

ISR(INT2_vect){
    PORTA ^= 1; // toggle first pin
}



void main(void) {
    customSetup();
    
    while(1){
        if(PSRRead() != 0){ // if what is received by SPI isn't 0, turn on LED
            PORTA |= (1 << 0);
        }else{ // else set it low
            PORTA &= ~(1 << 0);
        }
            
    }
}
