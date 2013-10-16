#ifndef _MARIO_H_
#define _MARIO_H_

#include "Sprite.h"

class Mario 
{
public:
	Mario(float x, float y);
	void draw(sf::RenderWindow* screen);
	void update(double interval);
	void setXspeed(double speed);
	sf::Vector2f getPosition();
private:
	cgf::Sprite sprite;
};

#endif
