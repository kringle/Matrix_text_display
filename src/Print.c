/*
 * Print.c
 *
 * Created: 23.07.2013 11:55:19
 *  Author: Kristian Windows
 */ 

#include "Print.h"
#include "Display.h"
#include "hsl2rgb.h"

volatile uint8_t	print_CharacterBlueVal	=	100	;
volatile uint8_t	print_CharacterGreenVal	=	200	;
volatile uint8_t	print_CharacterRedVal	=	0	;
volatile uint8_t	print_CharacterChangeCounter = 0;
volatile uint16_t	print_ColorH			= 0;
volatile uint8_t	print_ColorS			= 255;
volatile uint8_t	print_ColorL			= 127;
volatile uint8_t	printPos;

uint8_t				print_textBuffer[TEXTLENGTH];


void print_Setup( void )
{
	print_emptyBuffer();
	printPos = 0;
}

void print_ChangeColor( void )
{
	print_ColorH += 320;
	print_ColorH %= 768;
	uint8_t rgb_ar[3];
	hsl2rgb( print_ColorH, print_ColorS, print_ColorL, rgb_ar );

	print_CharacterRedVal = rgb_ar[0];
	print_CharacterGreenVal = rgb_ar[1];
	print_CharacterBlueVal = rgb_ar[2];


	/*

	print_CharacterBlueVal += 80;
	print_CharacterGreenVal += 70;
	print_CharacterRedVal += 21;
	*/
}



void print_emptyBuffer( void )
{
	for ( uint8_t i = 0; i < TEXTLENGTH ; ++i )
		print_textBuffer[i] = 0;
}


void print_OutputBuffer( uint8_t startPos )
{
	
	if ( startPos > TEXTLENGTH - 8 )
		{
			return;	
		}
		
	uint8_t rowCounter = 0;
	for ( uint8_t i = startPos ; i < startPos + 8 ; ++i)
	{
		for ( uint8_t j = 0 ; j < 8 ; ++j)
		{
			if ( print_textBuffer[i] & ( 1 << j ) )
			{
				DisplayData[rowCounter][j*3]		=	print_CharacterBlueVal;
				DisplayData[rowCounter][j*3 + 1]	=	print_CharacterGreenVal;
				DisplayData[rowCounter][j*3 + 2]	=	print_CharacterRedVal;
			}
		}
	rowCounter++;
	}

	// Change color every round
	if( print_CharacterChangeCounter >= 17 )
	{
		print_CharacterChangeCounter = 0;
		print_ChangeColor();
	}
	++print_CharacterChangeCounter;

}





void print_Character ( uint8_t startPos, uint8_t List[] )
{
	uint8_t counter = 0;
	for ( uint8_t i = startPos ; i < startPos + 8 ; ++i)
		{
			print_textBuffer[i] = pgm_read_byte ( & ( List[counter++] ) );	
		}
	//TODO : Find a sensible way to introduce a new character to an established string...
}


void print_CharInputCharacter( uint8_t startPos, char c )
{
	if ( startPos + 8 > TEXTLENGTH )
		return;
		
		
	switch ( c )
	{
		
		case ( 65 ):											//A,a
		case ( 97 ):
			print_Character	( startPos,	CharacterA );
			break;
			
		case( 69  ):											//E,e
		case( 101 ):
			print_Character( startPos, CharacterE );
			break;
			
		case ( 71 ):											// G,g
		case ( 103 ):
			print_Character	( startPos,	CharacterG );
			break;
			
		case ( 77 ):
		case ( 109 ):
			print_Character ( startPos, CharacterM );			// M,m
			break;
		
		case ( 79 ):
		case ( 111 ):
			print_Character	( startPos, CharacterO );				//O,o
			break;
		
		case  (82 ):
		case ( 114 ):
			print_Character ( startPos, CharacterR );			//R,r
			break;
			
		case ( 86 ):											//V,v
		case ( 118 ):
			print_Character ( startPos, CharacterV );
			break;
		
		default:												//if unknown character, display Omega
			print_Character( startPos, CharacterOmega );
			break;
	}
}