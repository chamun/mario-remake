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
#include "InputManager.h"
#include "Player.h"
#include "World.h"

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
    static PlayState m_PlayState;
    cgf::InputManager* im;
	Player* player;
	World *world;
	std::string levels[2];
	int levelIndex = 0;
};

#endif
