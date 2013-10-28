#include "include/Player.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player(float x, float y) 
{
	pos = sf::Vector2<float>(x, y);
}

void Player::draw(sf::RenderTarget *target)
{
	sf::RectangleShape shape(sf::Vector2<float>(16,16));
	shape.setFillColor(sf::Color(0xEA, 0xC5, 0xEA, 0xFF));
	shape.setOutlineColor(sf::Color(0xFF, 0x99, 0xFF, 0xFF));
	shape.setOutlineThickness(1);
	shape.setPosition(pos);

	target->draw(shape);
}

void Player::setPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Player::setXDirection(int direction)
{
	xDirection = direction;
}

void Player::setJumpPressed(bool value) { 
	jumpPressed = value; 
}

void Player::setRunning(bool value) { 
	isRunning = value; 
}

void Player::update(float dt)
{
	dt = 100 * (1/dt);

	/* X axis */
	float xVelocity     = isRunning ? RUNNING_VELOCITY : WALK_VELOCITY;
	float xAcceleration;
	if (isRunning)
		xAcceleration = RUNNING_ACCELERATION;
	else {
		if (fabs(currSpeed.x) <= WALK_VELOCITY)
			xAcceleration = 1;
		else
			xAcceleration = STOP_RUNNING_ACCELERATION;
	}

	float xTargetSpeed  = xVelocity * xDirection;
	float xNewDirection = signum(xTargetSpeed - currSpeed.x);
	currSpeed.x += xNewDirection * xAcceleration * dt;
	if (signum(xTargetSpeed - currSpeed.x) != xNewDirection) currSpeed.x = xTargetSpeed;
	
	/* Update Position */
	pos += currSpeed;
}


void Player::setFalling(bool falling)
{
}

int Player::signum(float n)
{
       if (n < -ZERO_THRESHOLD)
               return -1;
       if (n > ZERO_THRESHOLD)
               return 1;
       return 0;
}
