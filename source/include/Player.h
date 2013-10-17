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

class Player
{
    public:

	Player(float x, float y);
	void draw(sf::RenderTarget *target);

    private:

	sf::Vector2<float> pos;
};

#endif
