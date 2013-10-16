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
#include "include/Mario.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{
	player = new Mario(0, 16 * 32);

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
	map = new tmx::MapLoader("data/maps");
	map->Load("map1.tmx");
}

void PlayState::cleanup()
{
	delete player;
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
	player->setXspeed(dirx*100);
    player->update(game->getUpdateInterval());
	centerMapOnPlayer(game->getScreen());
}

void PlayState::draw(cgf::Game* game)
{
    sf::RenderWindow* screen = game->getScreen();
    //screen->draw(player);
	map->Draw(*screen);
	player->draw(screen);
}

void PlayState::centerMapOnPlayer(sf::RenderWindow* screen)
{
    sf::View view = screen->getView();
    sf::Vector2f viewsize = view.getSize();
    sf::Vector2u mapsize = map->GetMapSize();
    viewsize.x /= 2;
    viewsize.y /= 2;
    sf::Vector2f pos = player->getPosition();

    float panX = viewsize.x; // minimum pan
    if(pos.x >= viewsize.x)
        panX = pos.x;

    if(panX >= mapsize.x - viewsize.x)
        panX = mapsize.x - viewsize.x;

    float panY = viewsize.y; // minimum pan
    if(pos.y >= viewsize.y)
        panY = pos.y;

    if(panY >= mapsize.y - viewsize.y)
        panY = mapsize.y - viewsize.y;

    view.setCenter(sf::Vector2f(panX,panY));
    screen->setView(view);
}
