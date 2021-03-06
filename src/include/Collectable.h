#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "ActionHandler.h"
#include "Sprite.h"

class Collectable
{
    public:

    virtual void actionOnContact(ActionHandler *handler) = 0;
	virtual void getLogicalBox(sf::Rect<float> &rect) = 0;

	sf::Vector2f getPosition() { return pos; }
	float getWidth() { return width; }
	float getHeight() { return height; }

	void update(float interval) { sprite.update(interval); }

	virtual void draw(sf::RenderTarget *target) { target->draw(sprite); }

    protected:

    Collectable(float x, float y, float width, float height) {
		pos = sf::Vector2f(x, y);	
		this->width = width;
		this->height = height;
	}


	cgf::Sprite sprite;

	private:

	sf::Vector2f pos;
	float width;
	float height;
};

#endif // COLLECTABLE_H
