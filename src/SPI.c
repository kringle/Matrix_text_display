/*
 * SPI.c
 *
 * Created: 22.07.2013 17:49:54
 *  Author: Kristian Windows
 */ 

#include "SPI.h"





void SPI_setup ( void )  
{	
	PORTC.OUT = 0xFF;
	
	PORTC.DIR = 0b10111111; // PORTC set as output;
	
	SPIC.CTRL |= SPI_ENABLE_bm | SPI_CLK2X_bm | SPI_MASTER_bm;
	SPIC.CTRL |= SPI_PRESCALER_DIV4_gc;
	
	//SPIC.CTRL |= ( 1 << 2) | ( 1 << 3);
	
	SPIC.INTCTRL |= ( 1 << 0 ); // interrupt level for SPIC set to low
	// this is to ensure that the interrupts
	// for the TWI gets through
}
// sets up SPIC:
// prescaler			4
// interrupt level		low
// 2x mode				enabled


void SPI_blankAndLatch ( void )			
{
	PORTC.OUT |= (1 << 3 ) | ( 1 << 2 ); 
	PORTC.OUT &= ~ ( ( 1 << 3 ) | ( 1 << 2 ) ) ;
}
// pulse the Blank and latch-Pins;


void SPI_update ( void )
{
	SPIC.INTCTRL |= ( 1 << 0 ); // interrupt level for SPIC set to medium
}
// enables SPI-interrupts, thereby triggering update of the display with current data

ISR ( SPIC_INT_vect )
{
	static uint8_t		_12bytesSent	= 0;
	static uint8_t		_8bytesSent		= 0;
	static uint8_t		row				= 0;
	
	static uint16_t		first12Bits		= 0;
	static uint16_t		second12Bits	= 0;
	
	uint8_t				c				= 0;
	uint8_t				MSB_filter_var	= 0;
	
	
/*
	The data is sent in batches of two 12bits variables, divided into three 8bits variables. ( 12*2 == 8*3 )
	The sending of the two 12bits variables are divied into three actions, each one choosing the appropriate bits
	to put into the 8bit variable c, which is transmitted once the switch ends.
*/
		
	switch ( _8bytesSent % 3 )			
	{
		case ( 0 ):
			first12Bits = pgm_read_word(  & (  BrightnessLookUpTable[  DisplayData[row][_12bytesSent]  ]  )  );
			c = ( uint8_t ) (first12Bits >> 4);
			
			break;
	
		// case 0: read out the 16bits value from the lookupTable. Send MSB
	

		case( 1 ):
			
			second12Bits = pgm_read_word ( & ( BrightnessLookUpTable[ DisplayData[row][++_12bytesSent]  ]  ) );
			c = (uint8_t) ( first12Bits << 4 );
			MSB_filter_var = ((uint8_t) ( second12Bits >> 8 ))  & 0x0F;
			c |= MSB_filter_var;
			
			break;
		
		/*	case 1: read out the second 16bit value from the lookuptable.
			NB: if c is OR-ed directly with the 4 MSB of second12Bits,
				the results are unpredictable and leads to strange behaviour. 
				The MSB_filter_var eliminates these bits away.
		*/
			
		case( 2 ):
		
			c = (uint8_t) second12Bits;
			_12bytesSent++;
			break;
		// second12Bits has correct value because of static property		
	
		break;
		
		
		}
		
		SPIC.DATA = c;                  // send data
		_8bytesSent++;
		
		if ( _12bytesSent >= 24  || _8bytesSent >= 36 )					// if reached end
		{
			SPI_blankAndLatch();
			
			SPIC.INTCTRL	&=		~( ( 1 << 0 ) | ( 1 << 1 ) );		// turn off interrupts
			_12bytesSent	=		0;
			_8bytesSent		=		0;
			PORTA.OUT		=		~( 1 << row );						// switch to the correct row
			
			if ( ++row > 7)													
				row = 0;
		}	
}


