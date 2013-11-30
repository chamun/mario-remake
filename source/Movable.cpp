#include <iostream>
#include <cmath>
#include "include/Movable.h"


int Movable::signum(float n)
{
       if (n < -ZERO_THRESHOLD)
               return -1;
       if (n > ZERO_THRESHOLD)
               return 1;
       return 0;
}

void Movable::applyUpdate()
{
	pos += currSpeed;
}

void Movable::getLogicalBox(sf::Rect<float> &rect)
{
	rect.left = getX();
	rect.top  = getY();
	rect.height = getHeight();
	rect.width  = getWidth();
}

void Movable::setMovementRect(sf::Rect<float> &movement)
{
	float nx = pos.x + currSpeed.x; 
	float ny = pos.y + currSpeed.y;

	float left = fmin(pos.x, fmin(nx, fmin(pos.x + width, nx + width)));
	float right = fmax(pos.x + width, nx + width);

	float top = fmin(pos.y, fmin(ny, fmin(pos.y + height, ny + height)));
	float bottom = fmax(pos.y + height, ny + height);

	movement.left   = left;
	movement.width  = fmax(right - left, width);

	movement.top    = top;
	movement.height = fmax(bottom - top, height);

}

void Movable::setOnTheGround(bool value)
{	
	std::cout << "Movable::setOnTheGround " << value << std::endl;		
}

void Movable::setPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Movable::setXDirection(int direction)
{
	xDirection = direction;
}
