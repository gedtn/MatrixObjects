/*
  MatrixObjects.cpp - Library for objects that can move around a LED
  matrix
  Created by Gerard Nash, October 16, 2016.
  Released into the public domain.
*/

#ifdef __AVR__
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#endif

#include "MatrixObjects.h"



/******************************* MATRIX OBJECT */
Matrix_8x8_tricolor::Matrix_8x8_tricolor() {
	Matrix_8x8_tricolor::fill(LED_OFF);
}
	
void Matrix_8x8_tricolor::setDevice(Adafruit_BicolorMatrix *led_matrix) {
	this->_led_matrix = led_matrix;
}
	
void Matrix_8x8_tricolor::setPattern(uint8_t start[8]) {

  uint8_t current_byte;

  for (int i = 0; i<8; i++) {
    current_byte = start[i];
    for (int j = 7; j>=0; j--) {
      if (current_byte & 1) {
        this->_matrix[i][j] = LED_GREEN;  
      }  else {
        this->_matrix[i][j] = LED_OFF;  
      }
      current_byte = current_byte >> 1;      
    }    
  }
}

void Matrix_8x8_tricolor::fill(uint16_t color) {

	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
		  this->_matrix[i][j] = color;  
		}    
	}
}

void Matrix_8x8_tricolor::setPixel(uint16_t x, uint16_t y, uint16_t color) {
	this->_matrix[x][y] = color;
}

void Matrix_8x8_tricolor::draw() {
	this->draw(true);
}

void Matrix_8x8_tricolor::draw(bool overwrite) {
	
	if (overwrite) 
		this->_led_matrix->clear();

    for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			this->_led_matrix->drawPixel(j, i, this->_matrix[i][j]);
		}    
	}
    
    this->_led_matrix->writeDisplay();
}

const uint8_t Matrix_8x8_tricolor::getHeight() {
	return this->_height;
}

const uint8_t Matrix_8x8_tricolor::getWidth() {
	return this->_width;
}


/******************************* PIXEL OBJECT  */
Matrix_Pixel::Matrix_Pixel() {
}

Matrix_Pixel::Matrix_Pixel(Matrix_8x8_tricolor *led_matrix, uint16_t x, uint16_t y, uint16_t color) {
	this->_led_matrix = led_matrix;
	this->_x = x-1;
	this->_y = y-1;
	this->_color = color;
	this->_led_matrix->setPixel(this->_x,this->_y,this->_color);
}

void Matrix_Pixel::setPos(uint16_t x, uint16_t y) {
	this->_x = x-1;
	this->_y = y-1;
	this->_led_matrix->setPixel(this->_x,this->_y,this->_color);
}

void Matrix_Pixel::shiftPos(uint16_t x_inc, uint16_t y_inc) {
	// Clear the old position, move and redraw
	this->clear();

	this->_x = (this->_x + x_inc) % this->_led_matrix->getWidth();
	this->_y = (this->_y + y_inc) % this->_led_matrix->getHeight();

	this->_led_matrix->setPixel(this->_x,this->_y,this->_color);
}

void Matrix_Pixel::setColor(uint16_t color) {
	this->_color = color;
	this->_led_matrix->setPixel(this->_x,this->_y,this->_color);
}

void Matrix_Pixel::clear() {
	this->_led_matrix->setPixel(this->_x,this->_y,LED_OFF);
}

uint16_t Matrix_Pixel::getX() {
	return this->_x;
}

uint16_t Matrix_Pixel::getY() {
	return this->_y;
}

uint16_t Matrix_Pixel::getColor() {
	return this->_color;
}


/** Moving pixel *******************************/ 
Matrix_Moving_Pixel::Matrix_Moving_Pixel() {
	this->_heading = 0;
	this->_velocity = 0;
	this->_skips = 0;
}

Matrix_Moving_Pixel::Matrix_Moving_Pixel(Matrix_8x8_tricolor *led_matrix, uint16_t x, uint16_t y, uint16_t color) :
	Matrix_Pixel(led_matrix, x, y, color) {}


// Reverse idea...the number of moves to skip
void Matrix_Moving_Pixel::setVelocity(uint8_t velocity) {
	this->_velocity = velocity;
}

// 0 is due north, 1 is north east, and so on
void Matrix_Moving_Pixel::setHeading(uint8_t heading) {
	this->_heading = heading;
}

void Matrix_Moving_Pixel::move() {

	// Only move if we have skipped enough steps
	if (this->_skips++ > this->_velocity) {
		this->_skips = 0;

		// Move to the new positon
		this->shiftPos(this->x_inc[this->_heading]
    				  ,this->y_inc[this->_heading]);
	}

}

void Matrix_Moving_Pixel::move(bool randomHeading) {
	//this->_heading = this->_heading + (random 
}

/***************************************************************************/


/******************************* RAINDROP OBJECT 

Matrix_Raindrop::Matrix_Raindrop(uint8_t col) {
	_col = col;
}
*/

/***************************************************************************/
