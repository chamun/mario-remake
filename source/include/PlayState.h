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

#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "tmxloader/MapLoader.h"
#include "Player.h"

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

    static PlayState m_PlayState;
    cgf::InputManager* im;
	tmx::MapLoader* map;
	sf::Sprite* bg;
	Player* player;
};

#endif
