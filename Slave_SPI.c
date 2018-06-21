#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define LCD_DATA PORTC                //LCD data port
#define ctrl PORTE
#define en PE5                         // enable signal
#define rw PE4                       // read/write signal
#define rs PE3                         //register select signal
#define ke PE2                   // keyboard enable signal
//#include <math.h>
int dataout=0x00;
int data,datain;
int f=0;

void LCD_cmd(unsigned char cmd)
 {
	 DDRC=0xFF; 
	 LCD_DATA=cmd;
	 //ctrl=(0<<rs)|(0<<rw)|(1<<en);
	 ctrl&=0xF7;
	 ctrl|=0x20;
	 _delay_ms(1);
	 ctrl&=0xDF;
	 //ctrl =(0<<rs)|(0<<rw)|(0<<en);
	 _delay_ms(10);
	 return;
 }
void init_LCD(void)
 {
	 LCD_cmd(0x38);                            // initialization of 16X2 LCD in 8bit mode
	 _delay_ms(1);
	 LCD_cmd(0x01);                                 // clear LCD
	 _delay_ms(1);
	 LCD_cmd(0x0E);                        // cursor ON
	 _delay_ms(1);
	 LCD_cmd(0x80);                     // —8 go to first line and –0 is for 0th position
	 _delay_ms(1);
	 return ;
 }

 void LCD_write(unsigned char data)
 { 
	 DDRC=0xFF; 
	 LCD_DATA= data;
	 //ctrl = (1<<rs)|(0<<rw)|(1<<en);
	 ctrl|=0x28;
	 _delay_ms(1);
	 ctrl&=0xDF;
	 //ctrl = (1<<rs)|(0<<rw)|(0<<en);
	 _delay_ms(10);
	 return ;
 }
void init (void)
{
    DDRB|=0x08;              //Set MOSI, SCK,
	PORTB|=0x01;
	SPCR =0xC0; //Enable SPI
	SPDR =0x00;
    SPSR=0x00;
	
	
}
/*void spi_transmit ()
{
     
	
	SPDR = dataout; 
    
	
		_delay_ms(1); 
	 
                         
}*/
 void LCD_write_string(unsigned char str[])             //store address value of the string in pointer *str
 {
	  int i=0;
	  while(str[i]!=0x00)                               // loop will go on till the NULL character in the string
	 {
		 LCD_write(str[i]);                            // sending data on LCD byte by byte
		 i++;
	 }
 }
 
  ISR(SPI_STC_vect)
 {
	 datain=SPDR;
	 if(f==1)
	 {
		SPDR=dataout;
		f=0; 
	 }
	 else
	 SPDR=0x00;
	 
 }
ISR(INT0_vect)
 {
	   f=1;
	   DDRC=0x00;
	   //ctrl |=(1<<ke)|(1<<en);
	   ctrl|=0x24; 
	   _delay_ms(1);
	   //ctrl &=(0<<ke)&(0<<en);
	   ctrl&=0xDB;
	   _delay_ms(10);
	   data = PINC;
	   dataout=data;
	    LCD_cmd(0x01);                                 // clear LCD
		_delay_ms(1);
		LCD_write('K');
		LCD_write('E');
		LCD_write('Y'); 
		if(data==0xFE)
		LCD_write(49);
		if(data==0xFD)
		LCD_write(50);
		if(data==0xFB)
		LCD_write(51);
		if(data==0xF7)
		LCD_write(52);
		_delay_ms(500);
		LCD_cmd(0x01);                                 // clear LCD
	    _delay_ms(1);
		LCD_write_string("1-FE2-FD3-FB4-F7");
	  
	   /*SPDR=data;
	   //f=1;
	    _delay_ms(500);
	   LCD_cmd(0x01);                                 // clear LCD
	   _delay_ms(1);
	   LCD_write_string("K1-FE K2-FD");
	  _delay_ms(100);*/
	  
	   
 } 


 

 /*ISR(TIMER0_OVF_vect)
 {
	 
	 if(f==199999)
	 {
		
		 if(data!=0)
		 {
			  LCD_cmd(0x01);                                 // clear LCD
			  _delay_ms(1);
		      LCD_write('K');
			  LCD_write('E');
			  LCD_write('Y'); 
			  if(data==0xFE)
			  LCD_write(49);
			  if(data==0xFD)
			  LCD_write(50);
			  data =dataout;
		 }
		 //SPDR=dataout;
		 //while((SPSR & 0x80) ==0);
		 //datain=SPDR;
		 f=0;
	 }
	 else
	 f++;	 		  
		  
 }*/	  
		 
		 
		 
 
 int main()
 {
	 
	 init();
	 DDRE|=0x3C;
	 EIMSK |= 0x01;					// Enable INT0
	 EICRA |= 0x02 ;	               // Trigger INT0 on rising edge 
	 init_LCD();
	 _delay_ms(10);
	 LCD_write_string("1-FE2-FD3-FB4-F7");
	 _delay_ms(100);
	 //TCCR0|=0x01;                   // Prescaler = FCPU=CPU_CLock
     //TIMSK|=0x01;                  //Enable Overflow Interrupt Enable
     //TCNT0=0;                            //Initialize Counter
	
	 /*do
	 {
		while((PINB&0x01)==1);
		SPDR=dataout;
		while((SPSR & 0x80) ==0 );   //Wait until transmission complete
		datain=SPDR;
	 }while(1);*/
	 sei();
    while(1);	 
	 return 0;
 }     