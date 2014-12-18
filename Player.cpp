#include "include/Player.h"
#include <SFML/Graphics.hpp>

Player::Player() : Movable()
{
	std::cout << "In Player's Constructor"<< std::endl;
	smallSprite.loadXML((char *) "data/sprites/smallMario.xml");
	smallSprite.loadAnimation((char *) "data/sprites/smallMarioAnimation.xml");
	bigSprite.loadXML((char *) "data/sprites/bigMario.xml");
	bigSprite.loadAnimation((char *) "data/sprites/bigMarioAnimation.xml");
	sprite = &smallSprite;
	sprite->setAnimRate(4);
}


void Player::draw(sf::RenderTarget *target)
{
	sprite->setPosition(pos.x, pos.y - spriteCorrection);
	target->draw(*sprite);
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

	/* Sprite update */
	std::string animation = sprite->getAnimation();
	bool runSpeed = fabs(currSpeed.x) > RUNNING_VELOCITY / 2;

	if (currSpeed.x != 0) {
		animation = "walk";
		sprite->setAnimRate(4);
		if (runSpeed) {
			animation = "run";
			sprite->setAnimRate(8);
		}
		if (signum(currSpeed.x) != signum(xDirection))
			animation = "slide";
	} else {
		animation = "standing";
	}

	if (currSpeed.y < 0)
		animation = "jump";
	if (currSpeed.y > 0 && !onGround)
		animation = "fall";
	if (!onGround && runSpeed)
		animation = "jump-running";

	sprite->setAnimation(animation);
	sprite->play();
}

void Player::grow() 
{
	if (!isSmall())
		return;
	pos.y -= growSize;
	height += growSize;
	sprite = &bigSprite;
	spriteCorrection = 3;
}

void Player::shrink()
{
	pos.y  += growSize;
	height -= growSize;
	sprite = &smallSprite;
	spriteCorrection = 6;
}

void Player::setXDirection(int direction)
{
	xDirection = direction;
	if (direction == MOVABLE_H_RIGHT)
		sprite->setMirror(false);
	if (direction == MOVABLE_H_LEFT)
		sprite->setMirror(true);
	sprite->play();
}
