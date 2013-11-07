#include "tmxloader/MapObject.h"
#include <string>

#ifndef TILE_H_
#define TILE_H_

enum class Kind { COLLISION, PRIZE, ONEWAY};

class Tile {

	public:

	Tile (const tmx::MapTile *tile);

	Kind getKind() { return kind; }
	std::string getKindStr();

	float getX() { return pos.x; }
	float getY() { return pos.y; }
	float getWidth()  { return width;  }
	float getHeight() { return height; }

	private:

	Kind kind = Kind::COLLISION;
	sf::Vector2f pos;
	float width, height;
};

#endif
