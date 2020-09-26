#pragma once
#include "Typedefs.h"

class Creature;

// Base class used to define GOAP roles
class Goals
{
public:
    Goals(Creature* owner) : mOwner(owner) {}
    ~Goals() {}

    virtual PairSet getWorldState() = 0;
    virtual PairSet getGoalState() = 0;

    virtual void onFinished() {}

protected:
    Creature* mOwner;
};
