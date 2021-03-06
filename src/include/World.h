#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

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

	bool isFinished() { return end; }

	private: 
	#define MAX_INVENCIBILITY_TIME 10 

	tmx::MapLoader *map;
	Player *player;
	sf::Sprite *bg;
	std::vector<Collectable *> collectables;
	std::vector<Enemy *> enemies;
	std::string level;
	float invencibilityTime;
	bool end = false;

	void checkCollisions();
	void checkMarkers(Movable *actor);
	void checkCollisionsOnX(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	void checkCollisionsOnY(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	Tile* getTile(int row, int col, Layer layer_index);
	void getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles);
	void checkCollectables();
	void checkPlayerEnemies();
	void restart();

	void loadCollectables();
	Collectable* makeCollectable(tmx::MapObject *obj);
	void loadEnemies();
	Enemy* makeEnemy(tmx::MapObject *obj);

	sf::Music music;

	sf::SoundBuffer coinSoundBuffer;
	sf::Sound coinSound;
	sf::SoundBuffer growSoundBuffer;
	sf::Sound growSound;
	sf::SoundBuffer jumpSoundBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer stompSoundBuffer;
	sf::Sound stompSound;
	sf::SoundBuffer lostLifeSoundBuffer;
	sf::Sound lostLifeSound;
	sf::SoundBuffer shrinkSoundBuffer;
	sf::Sound shrinkSound;
	sf::SoundBuffer clearSoundBuffer;
	sf::Sound clearSound;
	sf::SoundBuffer irisSoundBuffer;
	sf::Sound irisSound;
	
};

#endif
