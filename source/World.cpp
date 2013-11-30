#include <cfloat>

#include "include/World.h"
#include "include/TextureManager.h"
#include "include/tmxloader/MapObject.h"
#include "include/Tile.h"
#include "include/Coin.h"
#include "include/RedMushroom.h"

// simpleCoin, redMushroom

World::World(Player *player)
{
	this->player = player;
	this->player->setPosition(0, 352);

	map = new tmx::MapLoader("data/maps");

	/* Loading background */
	cgf::TextureManager *tm = cgf::TextureManager::getInstance();
	sf::Texture* tex = tm->findTexture((char *)"data/imgs/bg_simple.png");
	if (tex == NULL) {
		std::cout << "World: Init: could not find the texture for the background." << std::endl;
		exit(EXIT_FAILURE);
	}
	bg = new sf::Sprite(*tex);

}

void World::increaseLife() { std::cout << "World: Increase life" << std::endl;} 
void World::addCoin()      { std::cout << "World: Add coin" << std::endl;} 
void World::addMedallion() { std::cout << "World: Add Medallion" << std::endl;} 
void World::addCollectable(Collectable *collectable) { std::cout << "World: Add collectable" << std::endl;} 

void World::growPlayer()  
{ 
	std::cout << "World: Grow player" << std::endl;
	this->player->grow();
}

void World::setMap(std::string level)
{
	map->Load(level);
	loadCollectables();
}

void World::cleanup()
{
	delete(map);
	delete(bg);
//	collectables.clear();
}

void World::update(float interval)
{
	player->calculateUpdate(interval);

	checkCollisions();
	checkCollectables();

	/* apply update */
	player->applyUpdate();
}

void World::draw(sf::RenderWindow *screen)
{
	screen->draw(*bg);
	//map->Draw(*screen);
	map->Draw(*screen, static_cast<int>(Layer::BACKGROUND));
	map->Draw(*screen, static_cast<int>(Layer::ONEWAY));
	map->Draw(*screen, static_cast<int>(Layer::COLLISION));
	for(int i = 0; i < collectables.size(); i++) {
		collectables[i]->draw(screen);
	}
	player->draw(screen);
}

void World::checkCollisions()
{
	std::vector<Tile *> tiles;
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

void World::checkCollisionsOnX(std::vector<Tile *> &tiles, sf::Rect<float> &movement)
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

void World::checkCollisionsOnY(std::vector<Tile *> &tiles, sf::Rect<float> &movement)
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


void World::getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles)
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

Tile* World::getTile(int row, int col, Layer layer_index)
{
	int index = static_cast<int>(layer_index);
	tmx::MapLayer& layer = map->GetLayers()[index];
	int ncols = floor(map->GetMapSize().x / map->GetMapTileSize().x);
	tmx::MapTile *tile = &layer.tiles[row * ncols + col];

	if (tile->gid > 0)
		return new Tile(tile, layer_index);
	
	return NULL;
}

void World::loadCollectables() 
{

	collectables.clear();

	int index = static_cast<int>(Layer::COLLECTABLE);
	tmx::MapLayer& layer = map->GetLayers()[index];
	std::vector<tmx::MapObject>& objects = layer.objects;

	for (int i = 0; i < objects.size(); i++) {
		tmx::MapObject *obj = &objects[i];
		Collectable *c = makeCollectable(obj);
		if (c != NULL)
			collectables.push_back(c);
	}

}

Collectable * World::makeCollectable(tmx::MapObject *obj)
{
	std::string type = obj->GetPropertyString("type");
	float x = obj->GetPosition().x;
	float y = obj->GetPosition().y - 16;
	float width  = obj->GetAABB().width;
	float height = obj->GetAABB().height;

	if (type == "simpleCoin")
		return new Coin(x, y, width, height);
	if (type == "redMushroom")
		return new RedMushroom(x, y, width, height);

	return NULL;
}

void World::checkCollectables()
{
	bool *remove = new bool[collectables.size()];
	
	for (int i = 0; i < collectables.size(); i++)
	{
		Collectable *c = collectables[i];
		remove[i] = false;
		sf::Rect<float> pRect, cRect;
		player->getLogicalBox(pRect);
		c->getLogicalBox(cRect);
		if (pRect.intersects(cRect)) {
			remove[i] = true;
			c->actionOnContact(this);
		}
	}

	for (int i = 0; i < collectables.size(); i++)
		if (remove[i])
			collectables.erase(collectables.begin() + i);

	delete remove;
}
