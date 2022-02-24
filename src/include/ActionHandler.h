#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include "Collectable.h"

class Collectable;

class ActionHandler
{
    public:

	virtual void increaseLife() = 0;
	virtual void growPlayer() = 0;
	virtual void addCoin() = 0;
	virtual void addMedallion() = 0;
	virtual void addCollectable(Collectable *collectable) = 0;

    protected:

    ActionHandler() { }
};

#endif // ACTIONHANDLER_H
