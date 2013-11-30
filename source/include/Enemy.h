#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include "Movable.h"

class Enemy : public Movable
{
	public: 

	Enemy () : Movable () {}
	void draw(sf::RenderTarget *target);
};

#endif
