#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int count=0,i=0;
char c[]={'1','5','*','0','6','*','1','6'};
int ub,lb; 
ISR(TIMER0_OVF_vect)
{	
		if(i==99)
		{   
			  switch(c[count])
			  {
				  case '0':
				  {
					  ub=0x00;lb=0x3F;
					  break;
				  }
				  case '1':
				  {
					  ub=0x00;lb=0x06;
					  break;
				  }				  
				  case '5':
				  {
					  ub=0x08;lb=0x69;
					  break;
				  }				  
				  case '6':
				  {
					  ub=0x00;lb=0xFD;
					  break;
				  }
				  case '*':
				  {
					  ub=0x3F;lb=0xFF;
					  break;
				  }				  				  				  
			  }  
				PORTA=ub;
				PORTF|=0x04;
				_delay_us(1);
				PORTF&=0xFB;
				PORTA=lb;
				PORTF|=0x02;
				_delay_us(1);
				PORTF&=0xFD;
				PORTF&=0xF7;
				_delay_us(1);
				PORTG&=0xF8;
				PORTG|=(7-count);
			    _delay_us(300);
				PORTF|=0x08;
		    if(count==7)
				count =0;
			else 
				count++;
				i=0;
		}
		i++;		
}
int main(void)
{
	DDRA=0xFF;
	DDRF|=0x0E;
	DDRG|=0x0F;
	PORTF|=0x08;
	PORTF&=~(0x06);
	//PORTG|=0x08;
	PORTG&=0xF7;
	 // Prescaler = FCPU=CPU_CLock
   TCCR0|=(1<<CS00);

   //Enable Overflow Interrupt Enable
   TIMSK|=(1<<TOIE0);

   //Initialize Counter
   TCNT0=0;
   sei();
	while(1);
	return 0;
}