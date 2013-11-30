/*
 *  Player.h
 *  Character the player controls.
 *
 *  Created by Rodrigo Chamun
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Movable.h"

class Player : public Movable
{
    public:

	#define JUMP_VELOCITY -5 

	Player() : Movable() {}

	/* Movable overwrite */
	void draw(sf::RenderTarget *target);
	void calculateUpdate(float dt);
	void setOnTheGround(bool value);
	
	/* Own stuff */
	void setJumpPressed(bool value); 
	void setRunning(bool value); 
	void grow();
	void shrink();
	bool isSmall() { return height == 16; }

    private:

	#define RUNNING_VELOCITY           6 
	#define RUNNING_ACCELERATION       0.07f 
	#define STOP_RUNNING_ACCELERATION  (2 * RUNNING_ACCELERATION) 

	#define MAX_JUMP_TIME 15

	void allowJump();

	const int growSize = 12;

	float jumpTime = MAX_JUMP_TIME;

	bool isRunning     = false;
	bool isJumpPressed = false;
	bool canJump       = false;

};

#endif
