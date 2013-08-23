/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */


#define F_CPU 32000000

#include <util/delay.h>
#include <asf.h>
#include <avr/io.h>
#include "SPI.h"
#include "ProgmemData.h"
#include "Display.h"
#include "Print.h"
#include "Timer.h"
#include "TWI.h"





void setupAll ( void );
void setClockTo32MHz ( void );
void accel_TiltVisualizer ( void );



int main (void)
{
	
	setupAll();
	
	
	print_Character(8, CharacterOmega);
	

	for ( ;; )
	{
	//accel_TiltVisualizer();
// 	if ( yAvg < 0 && xAvg < 0)
// 		Display_drawLine(0,0,-xAvg/10 ,-yAvg / 20);
// 	_delay_ms(10);
// 	Display_Clear();	
		
	}
}



void setupAll ( void )
{
	PORTA.DIR = 0xFF;		//Direction of A set to OUT
	PORTA.OUT  = 0x00;		//All pins initially low
	
	sei();
	PMIC.CTRL |= 7 ;		//All level interrupts enabled

	setClockTo32MHz();
	SPI_setup();
	
	Timer_0_Setup();
	Timer_1_Setup();
	print_Setup();
	TWI_setup();
	
	Display_Setup();
	TWI_polledWriteSingleByte(0x2A, 0x07);			//turns active, fast read mode on, Low noise 
	
	SPIC.DATA = 0x00; // starts the SPI-transmissions
}

void setClockTo32MHz ( void ) {
	CCP = CCP_IOREG_gc;							// disable register security for oscillator update
	OSC.CTRL = OSC_RC32MEN_bm;					// enable 32MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));		// wait for oscillator to be ready
	CCP = CCP_IOREG_gc;							// disable register security for clock update
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;			// switch to 32MHz clock
}


void accel_TiltVisualizer ( void )
{
	
	if ( xAvg < 0){
		DisplayData[3][17] = -xAvg*2;
		DisplayData[3][20] = -xAvg*2;
		DisplayData[3][23] = -xAvg*2;
		DisplayData[4][17] = -xAvg*2;
		DisplayData[4][20] = -xAvg*2;
		DisplayData[4][23] = -xAvg*2;
	}
	else{
		DisplayData[3][17] = 0;
		DisplayData[3][20] = 0;
		DisplayData[3][23] = 0;
		DisplayData[4][17] = 0;
		DisplayData[4][20] = 0;
		DisplayData[4][23] = 0;
	}
	if ( xAvg > 0){
		DisplayData[3][8] = xAvg*2;
		DisplayData[3][5] = xAvg*2;
		DisplayData[3][2] = xAvg*2;
		DisplayData[4][8] = xAvg*2;
		DisplayData[4][5] = xAvg*2;
		DisplayData[4][2] = xAvg*2;
		
	}
	else{
		DisplayData[3][8] = 0;
		DisplayData[3][5] = 0;
		DisplayData[3][2] = 0;
		DisplayData[4][8] = 0;
		DisplayData[4][5] = 0;
		DisplayData[4][2] = 0;
		
	}
	if ( yAvg < 0){
		DisplayData[5][14] = -yAvg*2;
		DisplayData[6][14] = -yAvg*2;
		DisplayData[7][14] = -yAvg*2;
		DisplayData[5][11] = -yAvg*2;
		DisplayData[6][11] = -yAvg*2;
		DisplayData[7][11] = -yAvg*2;
	}
	else{
		DisplayData[5][14] = 0;
		DisplayData[6][14] = 0;
		DisplayData[7][14] = 0;
		DisplayData[5][11] = 0;
		DisplayData[6][11] = 0;
		DisplayData[7][11] = 0;
	}
	if ( yAvg > 0){
		DisplayData[0][13] = +yAvg*2;
		DisplayData[1][13] = +yAvg*2;
		DisplayData[2][13] = +yAvg*2;
		DisplayData[0][10] = +yAvg*2;
		DisplayData[2][10] = +yAvg*2;
		DisplayData[1][10] = +yAvg*2;
	}
	else{
		DisplayData[0][13] = 0;
		DisplayData[1][13] = 0;
		DisplayData[2][13] = 0;
		DisplayData[0][10] = 0;
		DisplayData[2][10] = 0;
		DisplayData[1][10] = 0;
		
	}
	if ( zAvg > 0){
	DisplayData[3][12]	=	zAvg*2;
	DisplayData[4][12]	=	zAvg*2;
	DisplayData[3][9]	=	zAvg*2;
	DisplayData[4][9]	=	zAvg*2;
	}
	else{
	DisplayData[3][12]	=	0;
	DisplayData[4][12]	=	0;
	DisplayData[3][9]	=	0;
	DisplayData[4][9]	=	0;
	}
	if ( zAvg < 0){
	DisplayData[3][14]	=	-zAvg*2;
	DisplayData[4][14]	=	-zAvg*2;
	DisplayData[3][11]	=	-zAvg*2;
	DisplayData[4][11]	=	-zAvg*2;
	}
	else{
	DisplayData[3][14]	=	0;
	DisplayData[4][14]	=	0;
	DisplayData[3][11]	=	0;
	DisplayData[4][11]	=	0;
	}
	_delay_ms(1);
	
	
}