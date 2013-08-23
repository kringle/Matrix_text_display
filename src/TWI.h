/*
 * TWI.h
 *
 * Created: 23.07.2013 22:34:07
 *  Author: Kristian Windows
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>


extern volatile int8_t xAvg;
extern volatile	int8_t yAvg;
extern volatile int8_t zAvg;
extern volatile uint8_t TWI_receivedData;



#define		ACCELEROMETER_WRITE_ADDRESS			0x38
#define		ACCELEROMETER_READ_ADDRESS			0x39
#define		WHO_AM_I_VAL						0x2A
#define		WHO_AM_I_ADDR						0x0D


void	TWI_setup					(	void	);
void	TWI_singleByteRead			(	uint8_t );
uint8_t TWI_polledWHOAMI			(	void	);
int8_t	TWI_polledReadSingleByte	(	uint8_t	);
void	TWI_polledWriteSingleByte	(	uint8_t address,	uint8_t data);

static void		testStatusRegisters			(	uint8_t	);
 void	testReceivedByte			(	uint8_t byteToTest,	uint8_t	rowNumber	);






#endif /* TWI_H_ */