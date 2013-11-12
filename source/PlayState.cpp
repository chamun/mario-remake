/* *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include <cfloat>
#include "include/Game.h"
#include "include/PlayState.h"
#include "include/InputManager.h"
#include "include/TextureManager.h"
#include "include/tmxloader/MapObject.h"
#include "include/Tile.h"

#define FLOOR 352

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

	map = new tmx::MapLoader("data/maps");
	map->Load("simple.tmx");

	/* Loading background */
	cgf::TextureManager *tm = cgf::TextureManager::getInstance();
	sf::Texture* tex = tm->findTexture((char *)"data/imgs/bg_simple.png");
	if (tex == NULL) {
		cout << "PlayState: Init: could not find the texture for the background." << endl;
		exit(EXIT_FAILURE);
	}
	bg = new sf::Sprite(*tex);

	/* Creates Player */
	player = new Player(0, FLOOR);

    cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
	delete(map);
	delete(bg);
	delete(player);
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

		if(event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space)
				game->toggleStats();
		}
    }

    if(im->testEvent("quit"))
        game->quit();

	player->setXDirection(PLAYER_H_NONE);
	if(im->testEvent("left"))
		player->setXDirection(PLAYER_H_LEFT);
	if(im->testEvent("right"))
		player->setXDirection(PLAYER_H_RIGHT);

	player->setJumpPressed(im->testEvent("jump"));
	player->setRunning(im->testEvent("run"));

}

bool PlayState::isPlayerOnTheGround() {
	return player->getY() >= FLOOR;
}

void PlayState::update(cgf::Game* game)
{
	player->calculateUpdate((float) game->getUpdateInterval());

	/* check collisions */
	checkCollisions();

	/* apply update */
	player->applyUpdate();
	
//	player->setPosition(player->getX(), fmin(FLOOR, player->getY()));
}

void PlayState::draw(cgf::Game* game)
{
    sf::RenderWindow* screen = game->getScreen();
	screen->draw(*bg);
	map->Draw(*screen);
	player->draw(screen);
}

void PlayState::checkCollisions()
{
	vector<Tile *> tiles;
	sf::Rect<float> movement;
	
	player->setMovementRect(movement);
	getTilesOnPath(movement, tiles);

	/* X axis */
	checkCollisionsOnX(tiles, movement);
	checkCollisionsOnY(tiles, movement);

	/* cleaning up */
	for (int i = 0; i < tiles.size(); i++)
		delete tiles[i];
}

void PlayState::checkCollisionsOnX(vector<Tile *> &tiles, sf::Rect<float> &movement)
{
	float minDist = FLT_MAX;
	float px = player->getX();

	if (player->getCurrentSpeedX() > 0)
		px += player->getWidth();

	for (int i = 0; i < tiles.size(); i++) {

		float distance = FLT_MAX;
		Tile *t = tiles[i];

		if (t->getLayer() == Layer::ONEWAY)
			continue;

		if (player->getY() + player->getHeight() <= t->getY())
			continue;

		if (px < t->getX()) {
			distance = t->getX() - px;
		} else if (px > (t->getX() + t->getWidth())) {
			distance = px - (t->getX() + t->getWidth());
		} else {
			/* TODO: inside */
			distance = 0;
		}

		minDist = fmin(minDist, distance);
	}

	float newSpeedx = fmin(minDist, fabs(player->getCurrentSpeedX()));
	player->setCurrentSpeedX(newSpeedx * player->getSpeedDirectionX());
}

void PlayState::checkCollisionsOnY(vector<Tile *> &tiles, sf::Rect<float> &movement)
{
	float minDist = FLT_MAX;
	float py = player->getY();

	if (player->getCurrentSpeedY() > 0)
		py += player->getHeight();


	for (int i = 0; i < tiles.size(); i++) {

		float distance = FLT_MAX;
		Tile *t = tiles[i];

		if (t->getLayer() == Layer::ONEWAY &&
			player->getY() + player->getHeight() > t->getY()) 
				continue;

		if (py < t->getY()) {
			distance = t->getY() - py;
		} else if (py > (t->getY() + t->getHeight())) {
			distance = py - (t->getY() + t->getHeight());
		} else {
			distance = 0;
		}

		if ((player->getX() + player->getWidth()) > t->getX() && 
		    (t->getX() + t->getWidth()) > player->getX())
			minDist = fmin(minDist, distance);
	}


	float newSpeedy = fmin(minDist, fabs(player->getCurrentSpeedY()));
	player->setCurrentSpeedY(newSpeedy * player->getSpeedDirectionY());

	if (minDist == 0) 
		player->setOnTheGround(true);
	else
		player->setOnTheGround(false);

}


void PlayState::getTilesOnPath(sf::Rect<float> movement, vector<Tile*> &tiles)
{
	sf::Vector2u tilesize = map->GetMapTileSize();

	int x1 = floor(movement.left / tilesize.x);
	int x2 = floor((movement.left + movement.width) / tilesize.x);
	int y1 = floor(movement.top / tilesize.y);
	int y2 = floor((movement.top + movement.height) / tilesize.y);

	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++) {
			// Colision
			Tile *t = getTile(j, i, Layer::COLLISION);
			if (t != NULL)
				tiles.push_back(t);

			// OneWay
			t = getTile(j, i, Layer::ONEWAY);
			if (t != NULL)
				tiles.push_back(t);

			// Blocks
		}

}

Tile* PlayState::getTile(int row, int col, Layer layer_index)
{
	int index = static_cast<int>(layer_index);
	tmx::MapLayer& layer = map->GetLayers()[index];
	int ncols = floor(map->GetMapSize().x / map->GetMapTileSize().x);
	tmx::MapTile *tile = &layer.tiles[row * ncols + col];

	if (tile->gid > 0)
		return new Tile(tile, layer_index);
	
	return NULL;
}
