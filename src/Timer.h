/*
 * Timer.h
 *
 * Created: 23.07.2013 00:03:25
 *  Author: Kristian Windows
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_H_
#define TIMER_H_


#ifndef CharacterSize
	#define CharacterSize(x)			( x * 8 )
	#define TEXTLENGTH					CharacterSize(20) + 8
#endif

#define		CLOCK_PRESCALER_DIV_2_bm		2
#define		CLOCK_PRESCALER_DIV_4_bm		3
#define		CLOCK_PRESCALER_DIV_1024_bm		7
#define		INTERRUPT_PRIORITY_HIGH			3
#define		INTERRUPT_PRIORITY_LOW			1


void		print_OutputBuffer	( uint8_t startPos );
void		Display_Clear		( void );
void		SPI_update			( void );
void			Timer_0_Setup		( void );
void			Timer_1_Setup		( void );  

extern uint8_t print_textBuffer[];
extern volatile uint8_t printPos;






#endif /* TIMER_H_ */