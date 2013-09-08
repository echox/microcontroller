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

	sei();

}

void ledTest() {

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
		_delay_ms(200);
		PORTB ^= BLUE;
}

int main() { 

	init();
	ledTest();

	_delay_ms(500);
	PORTB |= GREEN;
	
        while(1) { 
	}

}
