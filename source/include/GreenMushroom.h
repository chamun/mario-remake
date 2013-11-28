#ifndef GREENMUSHROOM_H
#define GREENMUSHROOM_H

#include "Mushroom.h"
#include <iostream>

class GreenMushroom : public Mushroom
{
	public:

	GreenMushroom() {
		std::cout << "Created Green Mushrrom" << std::endl;
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Green Mushrrom: actionOnContact" << std::endl;
		handler->increaseLife();
	}

};

#endif // GREENMUSHROOM_H
