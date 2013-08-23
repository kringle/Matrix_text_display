/*
 * Display.h
 *
 * Created: 22.07.2013 23:25:28
 *  Author: Kristian Windows
 */ 




#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>


extern uint8_t DisplayData[8][24];


void	Display_Setup			( void );
void	Display_Clear			( void ); 
void	Display_setPixelValue	( uint8_t x, uint8_t y, uint16_t value );



void	Display_drawLine		( uint8_t startx, uint8_t starty, uint8_t endx,uint8_t endy );



#endif /* DISPLAY_H_ */