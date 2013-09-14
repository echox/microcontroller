#include <avr/io.h>
#include <stdint.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 
#include <avr/sleep.h>
#include <avr/pgmspace.h>

// define pins

#define BUTTON1 (1<<PC5) 
#define BUTTON2 (1<<PC4) 
#define BUTTON3 (1<<PC3) 
#define BUTTON4 (1<<PC2) 

#define GREEN	(1<<PB1) 
#define BLUE	(1<<PB2) 
#define RED	(1<<PB3) 

volatile uint16_t fade;

// button states
volatile uint8_t buttons;

// counters to debounce buttons
volatile uint8_t button1_debounce;

const uint16_t pwmtable_10[64] PROGMEM = {
    0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10,
    11, 12, 13, 15, 17, 19, 21, 23, 26, 29, 32, 36, 40, 44, 49, 55,
    61, 68, 76, 85, 94, 105, 117, 131, 146, 162, 181, 202, 225, 250,
    279, 311, 346, 386, 430, 479, 534, 595, 663, 739, 824, 918, 1023
};

void init() {

fade=0;
	// enable LED
	DDRB |= GREEN;
	DDRB |= BLUE;
	DDRB |= RED;

	// button pullups
	PORTC |= BUTTON1;
	PORTC |= BUTTON2;
	PORTC |= BUTTON3;
	PORTC |= BUTTON4;

	// toggle OC0A on compare match
	TCCR0A = (1<<COM0A0);

	// setting timer prescaler to 64
	TCCR0B |= (1<<CS00);
	TCCR0B |= (1<<CS01);

	// timer interrupt at 124
	// should be 1ms
	OCR0A = 124;

	// enable timer compare match interrupt
	TIMSK0 |= (1<<OCIE0A);

	sei();

	buttons = 0;
	button1_debounce = 0;

	PORTB = 0;
}

void ledTest() {
	_delay_ms(2000);
}


void delay_ms(uint16_t milliseconds) {
    for (; milliseconds > 0; milliseconds--)
        _delay_ms (1);
}

void delay_us(uint16_t milliseconds) {
    for (; milliseconds > 0; milliseconds--)
        _delay_us (1);
}
 
ISR(TIMER0_COMPA_vect) {

	if(!(PINC & BUTTON1)) {
		button1_debounce++;
	} else if((PINC & BUTTON1) && (button1_debounce > 0)) {
		button1_debounce--;
	}

	if(button1_debounce >= 50) {
	//	buttons |= (1<<1);
		buttons=1;
		button1_debounce=50;
	} else {
	//	buttons &= ~(1<<1);
		buttons=0;
	}
}

int main() { 

	init();
	ledTest();

	_delay_ms(500);
//	PORTB |= GREEN;
	
        while(1) { 

//	if (buttons & (1<<1)) {
	if (buttons == 1) {
		PORTB = RED;
	} else {
		PORTB = 0;
	}
/*
		PORTB |= GREEN;
		_delay_ms(1);

		PORTB &= ~GREEN;
		_delay_ms(2);
*/
	}

}
