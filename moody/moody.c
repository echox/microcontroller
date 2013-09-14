#include <avr/io.h>
#include <stdint.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 
#include <avr/sleep.h>
#include <avr/pgmspace.h>

#define BUTTON1 (1<<PC5) 
#define BUTTON2 (1<<PC4) 
#define BUTTON3 (1<<PC3) 
#define BUTTON4 (1<<PC2) 

#define GREEN	(1<<PB1) 
#define BLUE	(1<<PB2) 
#define RED	(1<<PB3) 

volatile uint16_t fade;

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

//	TIMSK0 |= (1<<TOIE0);
//	TCCR0B = (1<<CS01); 

//	sei();

}

void ledTest() {
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;
		_delay_ms(250);
		PORTB ^= RED;
}


const uint16_t pwmtable_10[64] PROGMEM = {
    0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10,
    11, 12, 13, 15, 17, 19, 21, 23, 26, 29, 32, 36, 40, 44, 49, 55,
    61, 68, 76, 85, 94, 105, 117, 131, 146, 162, 181, 202, 225, 250,
    279, 311, 346, 386, 430, 479, 534, 595, 663, 739, 824, 918, 1023
};

void my_delay (uint16_t milliseconds) {
    for (; milliseconds > 0; milliseconds--)
        _delay_us (1);
}
 
ISR(TIMER0_OVF_vect) {
	PORTB = RED;
}


int main() { 

	init();
	ledTest();

	_delay_ms(500);
	PORTB |= RED;
	
        while(1) { 

		PORTB |= RED;
		_delay_us(1);

		PORTB &= ~RED;
		_delay_us(20);
//		my_delay(pwmtable_10[fade]);

if( fade >= 64) {
	fade=1;
}

/*
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
*/

	}

}
