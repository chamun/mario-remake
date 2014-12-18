#ifndef COIN_H
#define COIN_H

#include "Collectable.h"
#include <iostream>

class Coin : public Collectable
{
	public: 

	Coin(float x, float y, float width, float height) : Collectable(x, y, width, height)
	{
		sprite.loadXML((char *)"data/sprites/coins.xml");
		sprite.setPosition(getPosition());
		sprite.setFrameRange(0, 3);
		sprite.setAnimRate(8);
		sprite.play();
	}


    void actionOnContact(ActionHandler *handler) { handler->addCoin(); }

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

#endif
