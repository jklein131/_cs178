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

void delay()
{
	int i=0;
	while(i<14000)
	{
		++i;
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
		
		if(!(GET_BIT(PORTB,PINB1)))
		{	
			wait_avr(200);
			SET_BIT(PORTB,PINB0);
			wait_avr(200);	
			CLR_BIT(PORTB,PINB0);
		}
		else
		{
			CLR_BIT(PORTB,PINB0);	
		}
	
	}
};

