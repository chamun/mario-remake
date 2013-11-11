/*
 *  Player.h
 *  Character the player controls.
 *
 *  Created by Rodrigo Chamun
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#define ZERO_THRESHOLD 0.001f

class Player
{
    public:

	Player(float x, float y);
	void draw(sf::RenderTarget *target);

	void setXDirection(int x);
	float getXDirection();
	float getYDirection();

	void calculateUpdate(float dt);
	void applyUpdate();

	void setOnTheGround(bool value);
	void setPosition(float x, float y);

	float getX() { return pos.x; }
	float getY() { return pos.y; } 

	float getCurrentSpeedX() { return currSpeed.x; }
	float getCurrentSpeedY() { return currSpeed.y; }
	void  setCurrentSpeedX(float sx) { currSpeed.x = sx; }
	void  setCurrentSpeedY(float sy) { currSpeed.y = sy; }

	float getWidth() { return width; }
	float getHeight() { return height; }

	int signum(float n);
	
	void setJumpPressed(bool value); 
	void setRunning(bool value); 

	void setMovementRect(sf::Rect<float> &movement);

	#define PLAYER_H_RIGHT  1
	#define PLAYER_H_LEFT  -1
	#define PLAYER_H_NONE   0

    private:

	#define WALK_VELOCITY              1.5f
	#define RUNNING_VELOCITY           6 
	#define RUNNING_ACCELERATION       0.07f 
	#define STOP_RUNNING_ACCELERATION  (2 * RUNNING_ACCELERATION) 

	#define JUMP_VELOCITY -5 
	#define GRAVITY       0.14f
	#define MAX_JUMP_TIME 15

	void allowJump();

	sf::Vector2<float> pos;
	sf::Vector2<float> currSpeed = sf::Vector2<float>(0, 0);

	float height = 16;
	float width  = 16;

	float xDirection;
	float jumpTime = MAX_JUMP_TIME;

	bool isRunning     = false;
	bool isJumpPressed = false;
	bool onGround      = false;
	bool canJump       = false;

};

#endif
