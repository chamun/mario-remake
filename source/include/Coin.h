#ifndef COIN_H
#define COIN_H

#include "Collectable.h"
#include <iostream>

class Coin : public Collectable
{
	public: 

	Coin(float x, float y, float width, float height) : Collectable(x, y, width, height) {
		std::cout << "Created a  Coin" << std::endl;
	}

	void draw(sf::RenderTarget *target)
	{
		sf::RectangleShape shape(sf::Vector2<float>(getWidth() - 6, getHeight() - 6));
		shape.setFillColor(sf::Color(0xFF, 0xCC, 0x00, 0xFF));
		shape.setOutlineColor(sf::Color(0xFF, 0x99, 0x00, 0xFF));
		shape.setOutlineThickness(1);

		sf::Vector2f npos = sf::Vector2f(getPosition().x + 3, getPosition().y + 3);
		shape.setPosition(npos);

		target->draw(shape);
	}

    void actionOnContact(ActionHandler *handler) {
		std::cout << " Coin: actionOnContact" << std::endl;
		handler->addCoin();
	}

};

#endif
