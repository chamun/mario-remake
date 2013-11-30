#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "Sprite.h"
#include "tmxloader/MapLoader.h"
#include "Movable.h"
#include "Player.h"
#include "Sprite.h"
#include "Tile.h"
#include "Collectable.h"
#include "ActionHandler.h"
#include "Enemy.h"

class World : ActionHandler {

	public:

	World(Player *player);
	void update(float interval);
	void draw(sf::RenderWindow *screen);
	void cleanup();
	void setMap(std::string level);

	void increaseLife(); 
	void growPlayer();
	void addCoin();
	void addMedallion();
	void addCollectable(Collectable *collectable);

	private: 
	tmx::MapLoader *map;
	Player *player;
	sf::Sprite *bg;
	std::vector<Collectable *> collectables;
	std::vector<Movable *> enemies;


	void checkCollisions();
	void checkCollisionsOnX(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	void checkCollisionsOnY(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	Tile* getTile(int row, int col, Layer layer_index);
	void getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles);
	void checkCollectables();

	void loadCollectables();
	Collectable* makeCollectable(tmx::MapObject *obj);
	
};

#endif
