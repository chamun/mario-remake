#include <cfloat>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "include/World.h"
#include "include/TextureManager.h"
#include "include/tmxloader/MapObject.h"
#include "include/Tile.h"
#include "include/Coin.h"
#include "include/Enemy.h"
#include "include/RedMushroom.h"

// simpleCoin, redMushroom

World::World(Player *player)
{
	this->player = player;

	map = new tmx::MapLoader("data/maps");

	/* Loading background */
	cgf::TextureManager *tm = cgf::TextureManager::getInstance();
	sf::Texture* tex = tm->findTexture((char *)"data/imgs/bg_simple.png");
	if (tex == NULL) {
		std::cout << "World: Init: could not find the texture for the background." << std::endl;
		exit(EXIT_FAILURE);
	}
	bg = new sf::Sprite(*tex);

	music.openFromFile("data/sounds/theme.ogg");
	music.setLoop(true);
	music.setVolume(100);

	coinSoundBuffer.loadFromFile("data/sounds/smw_coin.wav");
	coinSound.setBuffer(coinSoundBuffer);
	growSoundBuffer.loadFromFile("data/sounds/smw_power-up.wav");
	growSound.setBuffer(growSoundBuffer);
	stompSoundBuffer.loadFromFile("data/sounds/smw_stomp.wav");
	stompSound.setBuffer(stompSoundBuffer);
	jumpSoundBuffer.loadFromFile("data/sounds/smw_jump.wav");
	jumpSound.setBuffer(jumpSoundBuffer);
	lostLifeSoundBuffer.loadFromFile("data/sounds/smw_lost_a_life.wav");
	lostLifeSound.setBuffer(lostLifeSoundBuffer);
	shrinkSoundBuffer.loadFromFile("data/sounds/smw_pipe.wav");
	shrinkSound.setBuffer(shrinkSoundBuffer);
	clearSoundBuffer.loadFromFile("data/sounds/smw_course_clear.wav");
	clearSound.setBuffer(clearSoundBuffer);
	irisSoundBuffer.loadFromFile("data/sounds/smw_iris.wav");
	irisSound.setBuffer(irisSoundBuffer);
}

void World::increaseLife() { std::cout << "World: Increase life" << std::endl;} 
void World::addMedallion() { std::cout << "World: Add Medallion" << std::endl;} 
void World::addCollectable(Collectable *collectable) { std::cout << "World: Add collectable" << std::endl;} 

void World::addCoin()      
{ 
	coinSound.play();
} 

void World::growPlayer()  
{ 
	std::cout << "World: Grow player" << std::endl;
	this->player->grow();
	growSound.play();
}

void World::restart()
{
	collectables.clear();
	enemies.clear();
	music.stop();
	lostLifeSound.play();
	sleep(3);
	setMap(level);
}

void World::setMap(std::string level)
{
	this->level = level;
	map->Load(level);
	loadCollectables();
	loadEnemies();
	invencibilityTime = 0;
	this->player->setPosition(0, 352);
	music.play();
	end = false;
}

void World::cleanup()
{
	delete(map);
	delete(bg);
	collectables.clear();
	enemies.clear();
}

void World::update(float interval)
{
	if (collectables.size() == 0) {
		end = true;
		music.stop();
		clearSound.play();
		sleep(8);
		irisSound.play();
		sleep(1);
		return;
	}
	float dt = 100 * (1/interval);

	invencibilityTime += interval / 60;

	player->calculateUpdate(dt);
	for(int i = 0; i < enemies.size(); i++)
		enemies[i]->calculateUpdate(dt);

	checkCollisions();
	checkCollectables();

	/* apply update */
	player->applyUpdate();

	/* check map bounds */
	if (player->getX() < 0)
		player->setPosition(0, player->getY());
	if (player->getX() + player->getWidth() > map->GetMapSize().x)
		player->setPosition(map->GetMapSize().x - player->getWidth(), player->getY());

	for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->applyUpdate();
		enemies[i]->update(interval);
	}

	for(int i = 0; i < collectables.size(); i++)
		collectables[i]->update(interval);
	player->updateSprite(interval);
}

void World::draw(sf::RenderWindow *screen)
{
	screen->draw(*bg);
	map->Draw(*screen, static_cast<int>(Layer::BACKGROUND));
	map->Draw(*screen, static_cast<int>(Layer::ONEWAY));
	map->Draw(*screen, static_cast<int>(Layer::COLLISION));
	for(int i = 0; i < collectables.size(); i++) {
		collectables[i]->draw(screen);
	}
	for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw(screen);
	}
	player->draw(screen);
}

void World::checkCollisions()
{
	std::vector<Tile *> tiles;
	sf::Rect<float> movement;
	
	player->setMovementRect(movement);
	getTilesOnPath(movement, tiles);
	checkCollisionsOnX(player, tiles, movement);
	checkCollisionsOnY(player, tiles, movement);

	for(int i = 0; i < enemies.size(); i++) {
		Movable *actor = enemies[i];
		actor->setMovementRect(movement);
		getTilesOnPath(movement, tiles);
		checkCollisionsOnY(actor, tiles, movement);
		checkMarkers(actor);
	}

	checkPlayerEnemies();

	/* cleaning up */
	for (int i = 0; i < tiles.size(); i++)
		delete tiles[i];
}

void World::checkCollisionsOnX(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement)
{
	float minDist = FLT_MAX;
	float px = actor->getX();

	if (actor->getCurrentSpeedX() > 0)
		px += actor->getWidth();

	for (int i = 0; i < tiles.size(); i++) {

		float distance = FLT_MAX;
		Tile *t = tiles[i];

		if (t->getLayer() == Layer::ONEWAY)
			continue;

		if (actor->getY() + actor->getHeight() <= t->getY())
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

	float newSpeedx = fmin(minDist, fabs(actor->getCurrentSpeedX()));
	actor->setCurrentSpeedX(newSpeedx * actor->getSpeedDirectionX());
}

void World::checkCollisionsOnY(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement)
{
	float minDist = FLT_MAX;
	float py = actor->getY();

	if (actor->getCurrentSpeedY() > 0)
		py += actor->getHeight();


	for (int i = 0; i < tiles.size(); i++) {

		float distance = FLT_MAX;
		Tile *t = tiles[i];

		if (t->getLayer() == Layer::ONEWAY &&
			actor->getY() + actor->getHeight() > t->getY()) 
				continue;

		if (py < t->getY()) {
			distance = t->getY() - py;
		} else if (py > (t->getY() + t->getHeight())) {
			distance = py - (t->getY() + t->getHeight());
		} else {
			distance = 0;
		}

		if ((actor->getX() + actor->getWidth()) > t->getX() && 
		    (t->getX() + t->getWidth()) > actor->getX())
			minDist = fmin(minDist, distance);
	}


	float newSpeedy = fmin(minDist, fabs(actor->getCurrentSpeedY()));
	actor->setCurrentSpeedY(newSpeedy * actor->getSpeedDirectionY());

	if (minDist == 0) 
		actor->setOnTheGround(true);
	else
		actor->setOnTheGround(false);

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

void World::loadEnemies() 
{

	enemies.clear();

	int index = static_cast<int>(Layer::ENEMIES);
	tmx::MapLayer& layer = map->GetLayers()[index];
	std::vector<tmx::MapObject>& objects = layer.objects;

	for (int i = 0; i < objects.size(); i++) {
		tmx::MapObject *obj = &objects[i];
		Enemy *e = makeEnemy(obj);
		if (e != NULL)
			enemies.push_back(e);
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

Enemy * World::makeEnemy(tmx::MapObject *obj)
{
	/* Set movement type */
	int movement = MOVABLE_H_NONE; 
	std::string type = obj->GetPropertyString("movement");
	if (type == "left")
		movement = MOVABLE_H_LEFT;
	if (type == "right")
		movement = MOVABLE_H_RIGHT;

	float x = obj->GetPosition().x;
	float y = obj->GetPosition().y - 16;

	return new Enemy(x, y, movement);
}

void World::checkMarkers(Movable *actor)
{
	int index = static_cast<int>(Layer::MARKER);
	tmx::MapLayer& layer = map->GetLayers()[index];
	std::vector<tmx::MapObject>& objects = layer.objects;

	sf::Rect<float> aRect;
	actor->getLogicalBox(aRect);
	for (int i = 0; i < objects.size(); i++) {
		tmx::MapObject *obj = &objects[i];
		float x = obj->GetPosition().x;
		float y = obj->GetPosition().y;
		float width  = obj->GetAABB().width;
		float height = obj->GetAABB().height;

		sf::Rect<float> oRect(x, y, width, height);

		if (aRect.intersects(oRect)) {
			actor->setCurrentSpeedX(actor->getCurrentSpeedX() * -1);
			actor->setXDirection(actor->getSpeedDirectionX());
		}

	}

	if (aRect.left <= 0 || 
	    (aRect.left + aRect.width >= map->GetMapSize().x)) {
		actor->setCurrentSpeedX(actor->getCurrentSpeedX() * -1);
		actor->setXDirection(actor->getSpeedDirectionX());
	}
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

	for (int i = collectables.size() - 1; i >= 0; i--)
		if (remove[i]) {
			delete collectables[i];
			collectables.erase(collectables.begin() + i);
		}

	delete remove;
}

void World::checkPlayerEnemies()
{
	sf::Rect<float> pRect;
	player->getLogicalBox(pRect);
	bool *remove = new bool[enemies.size()];

	for (int i = 0; i < enemies.size(); i++) {
		remove[i] = false;
		Enemy *enemy = enemies[i];
		sf::Rect<float> eRect;
		enemy->getLogicalBox(eRect);
		if (eRect.intersects(pRect)) {
			if (player->getCurrentSpeedY() > 0) {
				remove[i] = true;
				player->setCurrentSpeedY(JUMP_VELOCITY / 2);
				stompSound.play();
			} else if (invencibilityTime > MAX_INVENCIBILITY_TIME) {
				if (player->isSmall())
					restart();
				else {
					player->shrink();
					invencibilityTime  = 0;
					shrinkSound.play();
				}
			}
		}
	}

	for (int i = enemies.size() - 1; i >= 0; i--)
		if (remove[i]) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
}
