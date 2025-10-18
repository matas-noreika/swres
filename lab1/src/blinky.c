#include <avr/io.h>
#define F_CPU 1000000UL //set clock as 1MHz
#include <util/delay.h>

void main(void){
	
	//set PB5 as output
	DDRB |= (1<<5);
	

	while(1){
	
		PORTB ^= (1<<5);
	
		_delay_ms(1000);

	}	

}
