#include <avr/io.h>
#include <stdint.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 
#include <avr/sleep.h>

#define BUTTON1 (1<<PC5) 
#define BUTTON2 (1<<PC4) 
#define BUTTON3 (1<<PC3) 
#define BUTTON4 (1<<PC2) 

#define GREEN	(1<<PB1) 
#define BLUE	(1<<PB2) 
#define RED	(1<<PB3) 

volatile uint8_t color = 0;

void init() {

	// enable LED
	DDRB |= GREEN;
	DDRB |= BLUE;
	DDRB |= RED;

	// button pullups
	PORTC |= BUTTON1;
	PORTC |= BUTTON2;
	PORTC |= BUTTON3;
	PORTC |= BUTTON4;

	// pin change interrupts for buttons
	PCMSK1 |= PCINT13;
	PCMSK1 |= PCINT12;
	PCMSK1 |= PCINT11;
	PCMSK1 |= PCINT10;

	// enable pin change for buttons
	PCICR |= PCIE2;

//	sei();

}

void ledTest() {

_delay_ms(4000);
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;


		PORTB ^= BLUE;
		_delay_ms(250);
		PORTB ^= BLUE;
		_delay_ms(250);
		PORTB ^= BLUE;
		_delay_ms(250);
		PORTB ^= BLUE;

		PORTB ^= GREEN;
		_delay_ms(250);
		PORTB ^= GREEN;
		_delay_ms(250);
		PORTB ^= GREEN;
		_delay_ms(250);
		PORTB ^= GREEN;
}

ISR(PCINT2_vect) {

		PORTB ^= BLUE;
}

int main() { 

	init();
	ledTest();

	_delay_ms(500);
	PORTB |= GREEN;
	
        while(1) { 
		_delay_ms(100);


	if(!(PINC & BUTTON1)) {

		if (color == 0) {
			PORTB = GREEN;	
			color=color+1;
		} else if (color == 1) {
			PORTB = BLUE;
			color=color+1;
		} else if (color == 2) {
			PORTB = RED;
			color++;
		} else if (color == 3) {
			PORTB = 0;
			color=0;
		}

	}


	if(!(PINC & BUTTON2)) {
		PORTB ^= GREEN;
	}

	if(!(PINC & BUTTON3)) {
		PORTB ^= RED;
	}

	if(!(PINC & BUTTON4)) {
		PORTB ^= BLUE;
	}

	}

}
