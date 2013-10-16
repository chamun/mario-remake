/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "include/Game.h"
#include "include/PlayState.h"
#include "include/InputManager.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{

    dirx = 0; // direção do sprite: para a direita (1), esquerda (-1)
    diry = 0; // baixo (1), cima (-1)

    im = cgf::InputManager::instance();

    im->addKeyInput("left", sf::Keyboard::A);
    im->addKeyInput("right", sf::Keyboard::D);
    im->addKeyInput("up", sf::Keyboard::W);
    im->addKeyInput("down", sf::Keyboard::S);
    im->addKeyInput("run", sf::Keyboard::J);
    im->addKeyInput("jump", sf::Keyboard::K);

    im->addKeyInput("quit", sf::Keyboard::Escape);
    im->addKeyInput("stats", sf::Keyboard::Space);


    cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
    cout << "PlayState: Clean" << endl;
}

void PlayState::pause()
{
    cout << "PlayState: Paused" << endl;
}

void PlayState::resume()
{
    cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::Event event;
    sf::RenderWindow* screen = game->getScreen();

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
    }

    dirx = diry = 0;

    if(im->testEvent("left")) {
        dirx = -1;
	}
	else
    if(im->testEvent("right")){
        dirx = 1;
	}

    if(im->testEvent("quit"))
        game->quit();

    if(im->testEvent("stats"))
        game->toggleStats();
}

void PlayState::update(cgf::Game* game)
{
}

void PlayState::draw(cgf::Game* game)
{
    sf::RenderWindow* screen = game->getScreen();
}
