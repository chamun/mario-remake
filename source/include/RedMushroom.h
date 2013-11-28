#ifndef REDMUSHROOM_H
#define REDMUSHROOM_H

#include "Mushroom.h"
#include <iostream>

class RedMushroom : public Mushroom
{
	public:

	RedMushroom() {
		std::cout << "Created Red Mushroom" << std::endl;
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Red Mushroom: actionOnContact" << std::endl;
		handler->growPlayer();
	}

};

#endif // REDMUSHROOM_H
