/*
 * Timer.c
 *
 * Created: 23.07.2013 00:03:49
 *  Author: Kristian Windows
 */ 
#include "Timer.h"
#include "Display.h"
#include "TWI.h"


void Timer_0_Setup( void )
{
	TCC0.CTRLA |= CLOCK_PRESCALER_DIV_4_bm;
	TCC0.INTCTRLA |= INTERRUPT_PRIORITY_HIGH;
	TCC0.PER = 5000;
}
/*		Timer 0 is used for the periodic update of the Display		*/

void Timer_1_Setup( void )  
{
	TCC1.CTRLA |= CLOCK_PRESCALER_DIV_1024_bm;
	TCC1.INTCTRLA |= INTERRUPT_PRIORITY_LOW;
	TCC1.PER = 20000;
}

/*		
TEXTMODE: Timer 1 is used for the periodic printing of the text		
SNAKEMODE: Timer1 is used for peridically getting the accelerometerData
*/


ISR ( TCC0_OVF_vect )
{
	SPI_update();
}


ISR ( TCC1_OVF_vect )
{
// 	static uint8_t operationNumber = 0;
// 	int8_t x,y,z;
// 	 
// 	switch ( operationNumber)
// 	{
// 		case(0):
// 			
// 			x =	TWI_polledReadSingleByte(0x01);
// 			xAvg -= xAvg/5;
// 			xAvg+=x/3;
// 			operationNumber++;
// 			break;
// 		
// 		case(1):
// 			
// 			y	=	TWI_polledReadSingleByte(0x03);
// 			
// 			yAvg -=yAvg/5;
// 			yAvg+=y/3; 
// 			operationNumber++;
// 			break;
// 		
// 		case(2):
// 			
// 			z	=	TWI_polledReadSingleByte(0x05);
// 			zAvg -=zAvg/5;
// 			zAvg+=z/3;
// 			operationNumber = 0;
// 			break;
// 	}
// 	
	
	
	
	
	
	
	
	
	
	/////////////////////////////The following to be used in case of DisplayMode ///////////////////////////////////
	Display_Clear();
	if ( ++printPos > 16)
		printPos = 0;
	print_OutputBuffer(printPos);
	
	//TODO: Some kind of "Shift the text towards the right - function
}
