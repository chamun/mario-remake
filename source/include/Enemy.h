#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include "Movable.h"

class Enemy : public Movable
{
	public: 

	Enemy (float x, float y, int movement) : Movable (x, y) 
	{
		setXDirection(movement);
	}

	void draw(sf::RenderTarget *target);
};

#endif
