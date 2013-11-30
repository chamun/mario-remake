#include "include/Player.h"
#include <SFML/Graphics.hpp>

void Player::draw(sf::RenderTarget *target)
{
	sf::RectangleShape shape(sf::Vector2<float>(width, height));
	shape.setFillColor(sf::Color(0xEA, 0xC5, 0xEA, 0xFF));
	shape.setOutlineColor(sf::Color(0xFF, 0x99, 0xFF, 0xFF));
	shape.setOutlineThickness(1);
	shape.setPosition(pos);

	target->draw(shape);
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

void Player::calculateUpdate(float dt)
{
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

void Player::grow() 
{
	pos.y -= growSize;
	height += growSize;
}

void Player::shrink()
{
	pos.y  += growSize;
	height -= growSize;
}
