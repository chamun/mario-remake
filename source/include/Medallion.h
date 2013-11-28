#ifndef MEDALLION_H
#define MEDALLION_H

#include "Coin.h"
#include <iostream>

class Medallion: public Coin
{
	public:
	Medallion() {
		std::cout << "Created a Simple Coin" << std::endl;
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Medallion: actionOnContact" << std::endl;
		handler->addMedallion();
	}
};

#endif
