#pragma once
#include <map>
#include <queue>
#include "Typedefs.h"

namespace sf
{
    class Time;
}
class Action;

__interface IGoap
{
    virtual PairSet getWorldState() = 0;

    virtual void addToGoalState(Condition goal) = 0;
    virtual PairSet createGoalState() = 0;

    virtual void planFailed(PairSet failedGoal) = 0;
    virtual void planFound(PairSet goal, std::queue<Action*> actions) = 0;
    virtual void actionsFinished() = 0;
    virtual void planAborted(Action* aborter) = 0;
    virtual bool moveAgent(Action* nextAction, const sf::Time& deltaTime) = 0;
};