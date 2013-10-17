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
