#ifndef SIMPLECOIN_H
#define SIMPLECOIN_H

#include "Coin.h"
#include <iostream>

class SimpleCoin : public Coin
{
	public: 
	SimpleCoin() {
		std::cout << "Created a Simple Coin" << std::endl;
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << "Simple Coin: actionOnContact" << std::endl;
		handler->addCoin();
	}
};

#endif
