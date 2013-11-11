#include "tmxloader/MapObject.h"
#include <string>

#ifndef TILE_H_
#define TILE_H_

enum class Layer { BACKGROUND, ONEWAY, COLLISION, PRIZE};

class Tile {

	public:

	Tile (const tmx::MapTile *tile, Layer layer);

	Layer getLayer() { return layer; }
	std::string getKindStr();

	float getX() { return pos.x; }
	float getY() { return pos.y; }
	float getWidth()  { return width;  }
	float getHeight() { return height; }

	private:

	Layer layer;
	sf::Vector2f pos;
	float width, height;
};

#endif
