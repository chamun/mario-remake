#include <sstream>
#include "include/Tile.h"

std::string Tile::getKindStr() 
{
	std::stringstream info;
	info << "(" << pos.x << "," << pos.y <<") w:" << width << " h: " << height;

	std::string ret = "<none>";

	switch(layer) {
		case Layer::COLLISION:
			ret = "Collision";
			break;
		case Layer::ONEWAY:
			ret = "One-way";
			break;
		default:
			ret = "Default";
	}
	info << " " << ret;

	return  info.str();
}

Tile::Tile (const tmx::MapTile *tile, Layer layer)
{
	const sf::Sprite *sprite = &tile->sprite;

	pos = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y);
	width = sprite->getLocalBounds().width;
	height = sprite->getLocalBounds().height;
	this->layer = layer;
}
