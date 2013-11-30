#ifndef MOVABLE_H_
#define MOVABLE_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Movable
{

	public:

	#define ZERO_THRESHOLD 0.001f

	#define MOVABLE_H_RIGHT  1
	#define MOVABLE_H_LEFT  -1
	#define MOVABLE_H_NONE   0

	float getCurrentSpeedX() { return currSpeed.x; }
	float getCurrentSpeedY() { return currSpeed.y; }
	float getSpeedDirectionX() { return signum(currSpeed.x); }
	float getSpeedDirectionY() { return signum(currSpeed.y); }
	int signum(float n);
	void applyUpdate();
	void getLogicalBox(sf::Rect<float> &movement);
	void setCurrentSpeedX(float sx) { currSpeed.x = sx; }
	void setCurrentSpeedY(float sy) { currSpeed.y = sy; }
	void setMovementRect(sf::Rect<float> &movement);
	void setPosition(float x, float y);
	void setXDirection(int x);

	float getX() { return pos.x; }
	float getY() { return pos.y; } 
	sf::Vector2f getPosition() { return pos; } 
	float getWidth() { return width; }
	float getHeight() { return height; }


	virtual void draw(sf::RenderTarget *target) = 0;
	virtual void calculateUpdate(float dt);
	virtual void setOnTheGround(bool value); 

	protected:

	#define WALK_VELOCITY 1.5f
	#define GRAVITY       0.14f

	Movable() {}

	sf::Vector2<float> pos;
	sf::Vector2<float> currSpeed = sf::Vector2<float>(0, 0);

	float height = 16;
	float width  = 16;

	float xDirection;
	bool onGround = false;

};

#endif
