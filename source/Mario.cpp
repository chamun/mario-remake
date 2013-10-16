#include "include/Mario.h"

using namespace cgf;

Mario::Mario(float x, float y) {
    sprite.loadXML((char *)"data/img/mario.xml");
	sprite.loadAnimation((char *)"data/img/marioanim.xml");
    sprite.setFrameRange(0,15);
    sprite.setAnimRate(10);
	sprite.setAnimation((char *)"standing");
    sprite.setPosition(x,y);
    sprite.play();
}

void Mario::draw(sf::RenderWindow* screen)
{
	screen->draw(sprite);
}

void Mario::update(double interval)
{
	sprite.update(interval);
	double speed = sprite.getXspeed();

	if (speed == 0) {
		sprite.setAnimation("standing");
	} else {
		if (sprite.getAnimation() != "walking") {
			sprite.setAnimation("walking");
			sprite.play();
		}
	}
}

void Mario::setXspeed(double speed)
{
	sprite.setXspeed(speed);
	if (speed < 0) {
		sprite.setMirror(true);
	} else if (speed > 0) {
		sprite.setMirror(false);
	}
}

sf::Vector2f Mario::getPosition()
{
	return sprite.getPosition();
}
