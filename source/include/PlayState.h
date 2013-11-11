/*
 *  PlayState.h
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "tmxloader/MapLoader.h"
#include "Player.h"
#include "Tile.h"

class PlayState : public cgf::GameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    /* Implement Singleton Pattern */
    static PlayState* instance() { return &m_PlayState; }

    protected:
	PlayState() {}

    private:
	
	bool isPlayerOnTheGround();

	void checkCollisions();
	void checkCollisionsOnX(std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	void checkCollisionsOnY(std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	Tile* getTile(int row, int col, Layer layer_index);
	void getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles);

    static PlayState m_PlayState;
    cgf::InputManager* im;
	tmx::MapLoader* map;
	sf::Sprite* bg;
	Player* player;
};

#endif
