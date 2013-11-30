#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "include/Enemy.h"

void Enemy::draw(sf::RenderTarget *target)
{
		sf::RectangleShape shape(sf::Vector2<float>(getWidth(), getHeight()));
		shape.setFillColor(sf::Color(0x50, 0xFF, 0x50, 0xFF));
		shape.setOutlineColor(sf::Color(0x40, 0xCC, 0x40, 0xFF));
		shape.setOutlineThickness(1);

		sf::Vector2f npos = sf::Vector2f(getPosition().x, getPosition().y);
		shape.setPosition(npos);
		target->draw(shape);
}
