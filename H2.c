/*
 * GccApplication1.c
 *
 * Created: 1/22/2018 4:43:35 PM
 * Author : olaoluwa
 */ 

#include <avr/io.h>

#define SET_BIT(p,i)(p |= (1 << i)) 
#define CLR_BIT(p,i)((p) &= ~(1<< i))
#define GET_BIT(p,i)((p) & (1 << i))

#define XTAL_FRQ 8000000lu


void
wait_avr(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

void delay(unsigned short msec)
{
	volatile int i=0;
	while(i<msec*XTAL_FRQ*1000 )
	{
		++i;
	}
}

int wait_key(){
	DDRC = 0x00000000; /*control register */ 
	PORTC = 0x00000000; /* port register */
	while(1){
		for (int i = 0; i < 4;i++){ /* Goes through columns */ 
			SET_BIT(PORTC,i);
			for (int j=0; j < 4; j++){ /* goes through rows */
				SET_BIT(DDRC,(j+4));
				wait_avr(1);
				if(!GET_BIT(PORTC,(j+4))){ /*checks if column, and row are active */
					DDRC = 0x00; /*if active, return to default state */
					PORTC = 0x00;
					return i*4 + j; /*return key index */
				}
				CLR_BIT(DDRC,(j+4)); /*clear bit from active column */ 
				wait_avr(1);
			}
			
			CLR_BIT(PORTC,i);
		}
	}
	}

int main(void)
{
    /* Replace with your application code */
	//set input and output pins
	SET_BIT(DDRB,PINB0);
	CLR_BIT(DDRB,PINB1);
	//SET_BIT(PORTB,PINB0);

    while (1) 
    {
		/*
		SET_BIT(PORTC,PINC0);
		SET_BIT(DDRC,PINC0);
		if(GET_BIT(PORTC,PINC5)) {
					wait_avr(500);
					SET_BIT(PORTB,PINB0);
					wait_avr(500);
					CLR_BIT(PORTB,PINB0);
		}
		*/
		
		if(wait_key()){
			wait_avr(500);
			SET_BIT(PORTB,PINB0);
			wait_avr(500);
			CLR_BIT(PORTB,PINB0);
		}
		
	}
};
