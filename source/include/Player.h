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
	void setTargetSpeedX(float x);
	void update();

    private:

	#define MAX_SPEED 2.0f
	#define ACCELERATION 1.0f

	sf::Vector2<float> pos;
	sf::Vector2<float> targetSpeed = sf::Vector2<float>(0, 0);
	sf::Vector2<float> currSpeed = sf::Vector2<float>(0, 0);
	int signum(float n);
};

#endif
