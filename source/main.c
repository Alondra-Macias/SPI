/**
	\file 
	\brief 
		This is a starter file to use the Nokia 5510 LCD. 
		The LCD is connected as follows:
		reset-PDT0
		CE-GND
		DC-PTD3
		DIN-PTD2
		CLK-PTD1
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	25/09/2018
	\todo
	    The SPI device driver needs to be completed.
 */

 
#include "SPI.h"
#include "GPIO.h"
#include "Bits.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "stdint.h"
#include "SPI.h"
#include "Delay.h"

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const spi_config_t g_spi_config = {
							SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D, bit_1, bit_2} };

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
extern const uint8_t ITESO[504];


int main(void)
{
	uint8_t string1[]="ITESO"; /*! String to be printed in the LCD*/
	uint8_t string2[]="uMs y DSPs"; /*! String to be printed in the LCD*/
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

		for(;;) {	  
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			LCD_nokia_bitmap(&ITESO[0]); /*! It prints an array that hold an image, in this case is the initial picture*/
			delay(65000);
			LCD_nokia_clear();
			delay(65000);
     		LCD_nokia_clear();
     		LCD_nokia_goto_xy(25,0); /*! It establishes the position to print the messages in the LCD*/
			LCD_nokia_send_string(&string1[0]); /*! It print a string stored in an array*/
			delay(65000);
     		LCD_nokia_goto_xy(10,1);
			LCD_nokia_send_string(string2); /*! It print a string stored in an array*/
			delay(65000);
			LCD_nokia_goto_xy(25,2);
			LCD_nokia_send_char('2'); /*! It prints a character*/
			LCD_nokia_send_char('0'); /*! It prints a character*/
			LCD_nokia_send_char('1'); /*! It prints a character*/
			LCD_nokia_send_char('8'); /*! It prints a character*/
			delay(65000);

		}
	
	return 0;
}

