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

void Player::setTargetSpeedX(float x)
{
	float speed = MAX_SPEED;
	if (isRunning)
		speed = MAX_SPEED_RUNNING;
	targetSpeed.x = speed * signum(x);
}

void Player::setJumpPressed(bool value) { 
	jumpPressed = value; 
}

void Player::setRunning(bool value) { 
	isRunning = value; 
}

void Player::update()
{
	if(canJump && jumpPressed) {
		currSpeed.y = - TERMINAL_SPEED;
		canJump = false;
	}

	sf::Vector2<float> direction = targetSpeed - currSpeed;
	direction.x = signum(direction.x);
	direction.y = signum(direction.y);
	currSpeed += direction * ACCELERATION;
	sf::Vector2<float> diff = targetSpeed - currSpeed;

	if(signum(diff.x) != direction.x) currSpeed.x = targetSpeed.x;
	if(signum(diff.y) != direction.y) currSpeed.y = targetSpeed.y;


	if (currSpeed.y == 0 && !jumpPressed)
		canJump = true;

	pos += currSpeed;
}

void Player::setFalling(bool falling)
{
	if(falling)
		targetSpeed.y = TERMINAL_SPEED;
	else {
		targetSpeed.y = 0;
		currSpeed.y = 0;
	}
}

int Player::signum(float n)
{
	if (n < -ZERO_THRESHOLD)
		return -1;
	if (n > ZERO_THRESHOLD)
		return 1;
	return 0;
}
