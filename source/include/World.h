#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "Sprite.h"
#include "tmxloader/MapLoader.h"
#include "Player.h"
#include "Sprite.h"
#include "Tile.h"
#include "Collectable.h"

class World {

	public:

	World(Player *player);
	void update(float interval);
	void draw(sf::RenderWindow *screen);
	void cleanup();
	void setMap(std::string level);

	private: 
	tmx::MapLoader *map;
	Player *player;
	sf::Sprite *bg;
	std::vector<Collectable *> collectables;


	void checkCollisions();
	void checkCollisionsOnX(std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	void checkCollisionsOnY(std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	Tile* getTile(int row, int col, Layer layer_index);
	void getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles);

	void loadCollectables();
	Collectable* makeCollectable(tmx::MapObject *obj);
	
};

#endif