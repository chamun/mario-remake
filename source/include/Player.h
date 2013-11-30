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

    private:

	#define WALK_VELOCITY              1.5f
	#define RUNNING_VELOCITY           6 
	#define RUNNING_ACCELERATION       0.07f 
	#define STOP_RUNNING_ACCELERATION  (2 * RUNNING_ACCELERATION) 

	#define JUMP_VELOCITY -5 
	#define GRAVITY       0.14f
	#define MAX_JUMP_TIME 15

	void allowJump();

	const int growSize = 12;

	float jumpTime = MAX_JUMP_TIME;

	bool isRunning     = false;
	bool isJumpPressed = false;
	bool onGround      = false;
	bool canJump       = false;

};

#endif
