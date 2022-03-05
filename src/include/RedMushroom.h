#ifndef REDMUSHROOM_H
#define REDMUSHROOM_H

#include "Collectable.h"
#include <iostream>

class RedMushroom : public Collectable
{
	public:

	RedMushroom(float x, float y, float width, float height) : Collectable(x, y, width, height)
	{ 
		sprite.loadXML((char *)"data/sprites/redMushroom.xml");
		sprite.setPosition(getPosition());
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
