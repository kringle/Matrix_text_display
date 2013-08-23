/*
 * SPI.h
 *
 * Created: 22.07.2013 17:49:44
 *  Author: Kristian Windows
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#ifndef SPI_H_
#define SPI_H_



extern uint8_t				DisplayData[8][24];
extern const uint16_t		BrightnessLookUpTable[256] PROGMEM;



void	SPI_setup				( void );				
void	SPI_blankAndLatch		( void );		
void	SPI_update				( void );
void	SPIC_INT_vect			( void );

#endif /* SPI_H_ */