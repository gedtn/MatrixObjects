/*
  MatrixObjects.h - Library for objects that can move around a LED
  matrix
  Created by Gerard Nash, October 16, 2016.
  Released into the public domain.
*/
#ifndef MatrixObjects_h
#define MatrixObjects_h

#include "Arduino.h"
#include "Adafruit_LEDBackpack.h"
#include <sstream>
#include <string>
#include <random>

class Matrix_8x8_tricolor
{
    public:
		Matrix_8x8_tricolor();
		void setDevice(Adafruit_BicolorMatrix *led_matrix);
		void setPattern(uint8_t start[8]);
		void fill(uint16_t color);
		void setPixel(uint16_t x, uint16_t y, uint16_t color);
		void draw();
		void draw(bool overwrite);
		const uint8_t getWidth();
		const uint8_t getHeight();		
	protected:
		uint16_t _matrix[8][8];
		const uint8_t _width=8;
		const uint8_t _height=8;
    private:
		Adafruit_BicolorMatrix *_led_matrix;
};

class Matrix_Pixel
{
	public:
		Matrix_Pixel();
		Matrix_Pixel(Matrix_8x8_tricolor *led_matrix, uint16_t x, uint16_t y, uint16_t color);
		void setPos(uint16_t x, uint16_t y);
		void shiftPos(uint16_t x_inc, uint16_t y_inc);
		void setColor(uint16_t color);
		void clear();
		uint16_t getX();
		uint16_t getY();
		uint16_t getColor();
	protected:
		Matrix_8x8_tricolor *_led_matrix;
		uint16_t _x;
		uint16_t _y;
		uint16_t _color;
};

class Matrix_Moving_Pixel : public Matrix_Pixel
{
	public:
		Matrix_Moving_Pixel();
		Matrix_Moving_Pixel(Matrix_8x8_tricolor *led_matrix, uint16_t x, uint16_t y, uint16_t color);
		void setVelocity(uint8_t velocity);
		void setHeading(uint8_t heading);
		void move();
		void move(bool randomDirection);
	private:
		uint16_t _velocity;
		uint16_t _heading;
		uint16_t _skips;
		const uint16_t x_inc[8] = {0,1,1,1,0,-1.-1,-1};
		const uint16_t y_inc[8] = {1,1,0,-1,-1,-1,0,1};
		
};

/*
class Matrix_Raindrop
{
  public:
    Matrix_Raindrop(void);
    Matrix_Raindrop(uint16_t col);
  private:
    uint16_t _col;
};
*/


#endif
