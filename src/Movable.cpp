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

void Movable::setPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Movable::setXDirection(int direction)
{
	xDirection = direction;
}

void Movable::calculateUpdate(float dt)
{
	/* X axis */
	float xVelocity = WALK_VELOCITY;
	float xAcceleration = 1;

	float xTargetSpeed  = xVelocity * xDirection;
	float xNewDirection = signum(xTargetSpeed - currSpeed.x);
	currSpeed.x += xNewDirection * xAcceleration * dt;
	if (signum(xTargetSpeed - currSpeed.x) != xNewDirection) currSpeed.x = xTargetSpeed;
	
	currSpeed.y += GRAVITY * dt;
}

void Movable::setOnTheGround(bool value) { onGround = value; }
