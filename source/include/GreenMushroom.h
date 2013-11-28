#ifndef GREENMUSHROOM_H
#define GREENMUSHROOM_H

#include "Collectable.h"
#include <iostream>

class GreenMushroom : public Collectable
{
	public:

	GreenMushroom(float x, float y, float width, float height) : Collectable(x, y, width, height) {
		std::cout << "Created Green Mushrrom" << std::endl;
	}

	void draw(sf::RenderTarget *target)
	{
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Green Mushrrom: actionOnContact" << std::endl;
		handler->increaseLife();
	}

};

#endif // GREENMUSHROOM_H
