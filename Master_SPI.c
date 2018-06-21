

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int datain;
// volatile uint8_t f=0;//
 
int state=0x55;
void init (void)
{
    DDRB |=0x0F;              //Set MOSI, SCK,SS as Output 0-SS,1-SCK,2-MOSI
	DDRB &=0xF7;              //set MISO as input B3
	DDRG |=0x1F;             //select and enable lines for decoder G3-ACTIVE HIGH ENABLE G2,G1,G0-CBA SET AS OUTPUT
    SPCR =0x50;              //Enable SPI-6, Set as Master-4
	SPSR =0x00;            
	
} 

void spi_transmit (unsigned char data)
{
     
	
	SPDR = data; 
    while((SPSR & 0x80) ==0 );   //Wait until transmission complete
	_delay_ms(1); 
	 
                         
}
/*ISR(SPI_STC_vect)
 {
	  
		   datain=SPDR;
		   f=1;
		   if(datain!=0)
		   state=datain;
		   
 }*/
/*ISR(TIMER1_OVF_vect)
{
	//i++;
	//if(i==16)
	SPDR=0x00;
	PORTG=0x1F;
	_delay_us(3.5);//while((SPSR & 0X80)==0);       //Wait until transmission complete
	datain=SPDR;
	PORTG=0x10;
	
	if(datain!=0)
    state = datain;
	//{
		PORTG=0x19;
		//_delay_ms(1);  
		_delay_ms(1);   
		spi_transmit(0x44); 
		spi_transmit(state);
		PORTG=0x10;
		/*state=~(state);
		i=0;
	}*/
	
	//f=1;
	
					
//}

int main(void)
{
    init();
	
	//for(int i=0;i<1000;i++)
	//_delay_ms(200);
			PORTG=0x19;
			_delay_ms(1);   
			spi_transmit(0x04);
			spi_transmit(0x01);
			PORTG=0x10;
			_delay_ms(1);
	
			PORTG=0x19;
			_delay_ms(1);   
			spi_transmit(0x09); 
			spi_transmit(0x55);
			PORTG=0x10;
			_delay_ms(1);
	   
			PORTG=0x19;
			_delay_ms(1);   
			spi_transmit(0x0A); 
			spi_transmit(0x55);
			PORTG=0x10;
			_delay_ms(1);
	//TCCR0|=0x07;               // Prescaler = FCPU=CPU_CLock/256
    //TIMSK|=(1<<TOIE0);                  //Enable Overflow Interrupt Enable
    //TCNT0=0;
	                            //Initialize Counter
	/*TCCR1B |= (1 << CS11);
    // initialize counter
    TCNT1 = 0;
  
    // enable overflow interrupt
    TIMSK |= (1 << TOIE1);*/
  
    // enable global interrupts

	        
	//sei();
	while(1)
	{
		   
	
		//	while(f==0);
		
			SPDR=0x00;
			PORTG=0x1F; 
	        while((SPSR & 0X80)==0 );  //_delay_us(3.5);      //Wait until transmission complete
			datain=SPDR;
			_delay_us(20); 
			PORTG=0x10;
			
			if(datain!= 0)
			{
				state = datain;	
				//state|=0x80;	
			}
			
			PORTG=0x19;  
			_delay_ms(1);   
			spi_transmit(0x44); 
			spi_transmit(state); 
			
			PORTG=0x10;
			//_delay_ms(1);
			
			
			_delay_ms(27);
	}
	
	
	return 0;
}
	
		      
	