/*
 * Display.c
 *
 * Created: 22.07.2013 23:25:36
 *  Author: Kristian Windows
 */ 

#include "Display.h"

uint8_t DisplayData[8][24];


void Display_Setup( void )
{
	Display_Clear();
}


void Display_Clear ( void )
{
	for ( uint8_t i = 0 ; i < 8 ; ++i )
		for ( uint8_t j = 0; j < 24; ++j )
			DisplayData[i][j] = 0;
}

void	Display_setPixelValue	( uint8_t x, uint8_t y, uint16_t value )
{
	if  ( ( y < 0 || y > 7)  || ( x <0 || x > 23 ) )
		return;
	
	
	
	if ( value > 255 || value < -254  )
		DisplayData[y][x] = 255;
	
	else
		if ( value < 0 )
			DisplayData[y][x] = -value;
		else
			DisplayData[y][x] = value;
}

void Display_drawLine ( uint8_t startx, uint8_t starty, uint8_t endx,uint8_t endy )
{
	

	float stigningstall;							// lol, engelsk?
	if ( endx == startx )
		{
			if ( endy > starty)
				stigningstall = 100.0;
			else
				stigningstall = -100.0;
		}
	
	else	
		stigningstall = (float)(endy-starty) / (float) (endx-startx);									
	
	if ( !(stigningstall > -1.0  &&  stigningstall < 1.0 ))
	{
		if ( startx < endx ){
			for ( uint8_t x = startx; x < endx ; x+=3 )
			{
				uint8_t y = (stigningstall * ( x - startx )) + starty;
				DisplayData[y][(x / 3) * 3] = 100;
			}
		}
		else
		{
			for ( uint8_t x = endx; x > startx ; x-=3 )
				{
					uint8_t y = (stigningstall * ( x - endx )) + endy;
					DisplayData[y][(x / 3)*3] = 100;
				}
		}		
	}
	else
	{
		if ( starty < endy )
		{
			for ( uint8_t y = starty; y < endy ; y+=3 )
			{
				uint8_t x = ((y - starty )/ stigningstall) + startx;
				DisplayData[y][(x / 3)*3] = 100;
			}
		}
		else {
			
			for ( uint8_t y = endy; y > starty ; y-=3 )
			{
				uint8_t x = ((y - endy )/ stigningstall) + endx;
				DisplayData[y][(x / 3)*3] = 100;
			}
		}
		
	}
}

