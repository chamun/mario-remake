#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "Movable.h"
#include "Sprite.h"

class Enemy : public Movable
{
	public: 

	Enemy (float x, float y, int movement) : Movable (x, y) 
	{
		setXDirection(movement);
		if (movement < 0)
			sprite.setMirror(true);
		sprite.loadXML((char *)"data/sprites/enemy.xml");
		sprite.setPosition(getPosition());
		sprite.setFrameRange(0, 1);
		sprite.setAnimRate(4);
		sprite.play();
		WALK_VELOCITY = 0.75f;
	}

	void draw(sf::RenderTarget *target) 
	{ 
		sprite.setPosition(getPosition());
		target->draw(sprite);
	}

	void update(float interval) { 
		sprite.update(interval); 
		if (getSpeedDirectionX() > 0)
			sprite.setMirror(false);
		if (getSpeedDirectionX() < 0)
			sprite.setMirror(true);
	}

	private:

	cgf::Sprite sprite;
};

#endif
