#ifndef REDMUSHROOM_H
#define REDMUSHROOM_H

#include "Collectable.h"
#include <iostream>

class RedMushroom : public Collectable
{
	public:

	RedMushroom(float x, float y, float width, float height) : Collectable(x, y, width, height)
	{
		std::cout << "Created Red Mushroom" << std::endl;
	}

	void draw(sf::RenderTarget *target)
	{
		sf::RectangleShape shape(sf::Vector2<float>(getWidth() - 6, getHeight() - 6));
		shape.setFillColor(sf::Color(0xFF, 0x50, 0x50, 0xFF));
		shape.setOutlineColor(sf::Color(0xCC, 0x40, 0x40, 0xFF));
		shape.setOutlineThickness(1);

		sf::Vector2f npos = sf::Vector2f(getPosition().x + 3, getPosition().y + 3);
		shape.setPosition(npos);
		target->draw(shape);
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Red Mushroom: actionOnContact" << std::endl;
		handler->growPlayer();
	}

};

#endif // REDMUSHROOM_H
