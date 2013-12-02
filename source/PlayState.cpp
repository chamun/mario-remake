/* *  PlayState.cpp
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

    im = cgf::InputManager::instance();

    im->addKeyInput("left",  sf::Keyboard::A);
    im->addKeyInput("right", sf::Keyboard::D);
    im->addKeyInput("up",    sf::Keyboard::W);
    im->addKeyInput("down",  sf::Keyboard::S);
    im->addKeyInput("run",   sf::Keyboard::J);
    im->addKeyInput("jump",  sf::Keyboard::K);
    im->addKeyInput("quit",  sf::Keyboard::Escape);

	/* Creates Player */
	cout << "---------- Creating player" << endl;
	player = new Player();
	cout << "---------- Creating world" << endl;
	world  = new World(player);
	world->setMap("simple.tmx");

    cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
	world->cleanup();
	delete (player);
    cout << "PlayState: Clean" << endl;
}

void PlayState::pause()  { cout << "PlayState: Paused"  << endl; }
void PlayState::resume() { cout << "PlayState: Resumed" << endl; }

void PlayState::handleEvents(cgf::Game* game)
{
	sf::Event event;
	sf::RenderWindow* screen = game->getScreen();

	while (screen->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			game->quit();

		if(event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space)
				game->toggleStats();
		}
	}

	if(im->testEvent("quit"))
		game->quit();


	player->setXDirection(MOVABLE_H_NONE);
	if(im->testEvent("left"))
		player->setXDirection(MOVABLE_H_LEFT);
	if(im->testEvent("right"))
		player->setXDirection(MOVABLE_H_RIGHT);

	player->setJumpPressed(im->testEvent("jump"));
	player->setRunning(im->testEvent("run"));

}

void PlayState::update(cgf::Game* game)
{
	world->update((float) game->getUpdateInterval());
}

void PlayState::draw(cgf::Game* game)
{
    sf::RenderWindow* screen = game->getScreen();
	world->draw(screen);
}
