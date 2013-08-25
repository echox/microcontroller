#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 
#include <avr/sleep.h>

#define BUTTON1 (1<<PB1) 
#define LED     (1<<PB2) 


ISR(SIG_PIN_CHANGE) { 
	sleep_disable();
		int i =0;
		for(i=0;i<5;i++) {
			_delay_ms(500);
			PORTB ^= LED; 
		}
} 

int main() { 

        /* outputs */ 
        DDRB |= LED; 

        /* internal pullups */ 
        PORTB |= BUTTON1;

	PCMSK |= (1<<PCINT1);
	GIMSK |= (1<<PCIE);

	PORTB |= LED;

	sei();

        while(true) { 
cli();

	if (!(PINB & BUTTON1)) { 
                        /* toggle led */ 
//                        PORTB ^= LED; 

                        /* prinmitive debounce */ 
		_delay_ms(1000); 
		
		while(!(PINB & BUTTON1)) {
				_delay_ms(100);
               	        	PORTB ^= LED; 
		}

		sei();
		sleep_enable();
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_mode();
		
		delay_ms(100);
		PORTB ^= LED; 
		_delay_ms(100);
          	PORTB ^= LED; 
		_delay_ms(1000);
                PORTB ^= LED; 
		_delay_ms(100);
		PORTB ^= LED; 
		_delay_ms(100);
                PORTB ^= LED; 
	}
			
	} 
        
        /* NOTREACHED */ 
        return (0); 
}
