/*
 * Print.h
 *
 * Created: 23.07.2013 11:55:12
 *  Author: Kristian Windows
 */

#include <avr/io.h>
#include <avr/pgmspace.h>


#ifndef PRINT_H_
#define PRINT_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

	#ifndef CharacterSize
	#define CharacterSize(x)			( x * 8 )
	#define TEXTLENGTH					CharacterSize(20) + 8
	#endif

///////////////////// Extern Character Definitions ( located in ProgmemData.h ) ////////////////////////////
extern const char CharacterG[] PROGMEM;
extern const char CharacterA[] PROGMEM ;
extern const char CharacterM[] PROGMEM;
extern const char CharacterE[] PROGMEM;
extern const char CharacterO[] PROGMEM;
extern const char CharacterV[] PROGMEM;
extern const char CharacterR[] PROGMEM;
extern const char CharacterR_tilted[] PROGMEM;




extern const char CharacterOmega[] PROGMEM;

///////////////////////////////////////////////////////////////////////////////////////////////////////////











void	print_Setup					( void );
void	print_emptyBuffer			( void );
void	print_OutputBuffer			( uint8_t startPos );
void	print_Character				( uint8_t startPos, uint8_t List[] );
void	print_CharInputCharacter	( uint8_t startPos , char c );




#endif /* PRINT_H_ */