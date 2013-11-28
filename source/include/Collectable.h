#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "ActionHandler.h"

class Collectable
{
    public:

    virtual void actionOnContact(ActionHandler *handler) = 0;

    protected:

    Collectable() { }
};

#endif // COLLECTABLE_H
