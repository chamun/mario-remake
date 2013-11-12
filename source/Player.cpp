#include "include/Player.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player(float x, float y) 
{
	pos = sf::Vector2<float>(x, y);
}

void Player::draw(sf::RenderTarget *target)
{
	sf::RectangleShape shape(sf::Vector2<float>(width, height));
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

float Player::getYDirection()
{
	return signum(currSpeed.y);
}

float Player::getXDirection()
{
	return xDirection;
}

void Player::setJumpPressed(bool value) { 
	isJumpPressed = value; 
	if (!value && onGround) 
		allowJump();
}

void Player::setRunning(bool value) { 
	isRunning = value; 
}

void Player::setOnTheGround(bool value)
{
	onGround = value;	
	if (value && !isJumpPressed)
		allowJump();

	if (!value) {
		canJump = false;
	}
		
}

void Player::allowJump()
{
	canJump = true;
	jumpTime = 0;
}

void Player::applyUpdate()
{
	pos += currSpeed;
}

void Player::calculateUpdate(float dt)
{
	dt = 100 * (1/dt);

	/* X axis */
	float xVelocity = isRunning ? RUNNING_VELOCITY : WALK_VELOCITY;
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
	
	/* Y axis */
	if (canJump && isJumpPressed) {
		currSpeed.y = JUMP_VELOCITY;		
		canJump = false;
	} else 
	if (!canJump && isJumpPressed && jumpTime < MAX_JUMP_TIME) {
		jumpTime += dt;
		currSpeed.y += -GRAVITY * dt;
	}

	currSpeed.y += GRAVITY * dt;
}


int Player::signum(float n)
{
       if (n < -ZERO_THRESHOLD)
               return -1;
       if (n > ZERO_THRESHOLD)
               return 1;
       return 0;
}

void Player::setMovementRect(sf::Rect<float> &movement)
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
