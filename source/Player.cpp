#include "include/Player.h"
#include <SFML/Graphics.hpp>

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

void Player::setTargetSpeedX(float x)
{
	targetSpeed.x = MAX_SPEED * signum(x);
}

void Player::update()
{
	sf::Vector2<float> direction = targetSpeed - currSpeed;
	direction.x = signum(direction.x);
	direction.y = signum(direction.y);
	currSpeed += direction * ACCELERATION;
	pos += currSpeed;
}

int Player::signum(float n)
{
	if (n < -ZERO_THRESHOLD)
		return -1;
	if (n > ZERO_THRESHOLD)
		return 1;
	return 0;
}
