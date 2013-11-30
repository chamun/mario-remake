INCLUDES= -I/usr/local/include -Iinclude
LIBS= -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
FLAGS= -std=c++11 -g
CXX= g++-4.7 $(FLAGS)

OBJS= main.o Game.o Player.o PlayState.o InputManager.o \
      Sprite.o TextureManager.o pugixml.o MapLoaderPrivate.o \
	  MapLoaderPublic.o QuadTreeNode.o Tile.o World.o Movable.o

all : $(OBJS)
	$(CXX) -o ../bin/game $(OBJS) $(INCLUDES) $(LIBS)

main.o : main.cpp
	$(CXX) -c main.cpp

Game.o: Game.cpp include/Game.h
	$(CXX) -c Game.cpp

PlayState.o: PlayState.cpp include/PlayState.h
	$(CXX) -c PlayState.cpp

InputManager.o : InputManager.cpp include/InputManager.h
	$(CXX) -c InputManager.cpp

Sprite.o : Sprite.cpp include/Sprite.h
	$(CXX) -c Sprite.cpp

TextureManager.o: TextureManager.cpp include/TextureManager.h
	$(CXX) -c TextureManager.cpp

pugixml.o : pugixml/pugixml.cpp
	$(CXX) -c pugixml/pugixml.cpp -Iinclude

MapLoaderPrivate.o:	tmxloader/MapLoaderPrivate.cpp
	$(CXX) -c tmxloader/MapLoaderPrivate.cpp -Iinclude

MapLoaderPublic.o:	tmxloader/MapLoaderPublic.cpp
	$(CXX) -c tmxloader/MapLoaderPublic.cpp -Iinclude

QuadTreeNode.o:	tmxloader/MapLoaderPrivate.cpp
	$(CXX) -c tmxloader/QuadTreeNode.cpp -Iinclude

Player.o: Player.cpp include/Player.h include/Movable.h
	$(CXX) -c Player.cpp

Tile.o: Tile.cpp include/Tile.h
	$(CXX) -c Tile.cpp

World.o: World.cpp include/World.h include/Coin.h include/RedMushroom.h
	$(CXX) -c World.cpp

Movable.o: Movable.cpp include/Movable.h
	$(CXX) -c Movable.cpp

clean:
	rm -f *.o
