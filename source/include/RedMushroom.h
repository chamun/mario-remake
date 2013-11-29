#ifndef REDMUSHROOM_H
#define REDMUSHROOM_H

#include "Collectable.h"
#include <iostream>

class RedMushroom : public Collectable
{
	public:

	RedMushroom(float x, float y, float width, float height) : Collectable(x, y, width, height) { }

	void draw(sf::RenderTarget *target)
	{
		sf::RectangleShape shape(sf::Vector2<float>(getWidth() - marginx * 2, getHeight() - marginy * 2));
		shape.setFillColor(sf::Color(0xFF, 0x50, 0x50, 0xFF));
		shape.setOutlineColor(sf::Color(0xCC, 0x40, 0x40, 0xFF));
		shape.setOutlineThickness(1);

		sf::Vector2f npos = sf::Vector2f(getPosition().x + marginx, getPosition().y + marginy);
		shape.setPosition(npos);
		target->draw(shape);
	}

    void actionOnContact(ActionHandler *handler) { handler->growPlayer(); }

	void getLogicalBox(sf::Rect<float> &rect)
	{
		rect.left = getPosition().x + marginx;
		rect.top  = getPosition().y + marginy;
		rect.width  = getWidth()  - marginx * 2;
		rect.height = getHeight() - marginy * 2;
	}

	private:

	const int marginx = 3;
	const int marginy = 3;
};

#endif // REDMUSHROOM_H
