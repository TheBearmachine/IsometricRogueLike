#include "GoalsControllable.h"
#include "ActionHelper.h"

GoalsControllable::GoalsControllable(Creature * owner) : Goals(owner)
{
    addToWorldState(ActionHelper::Conditions::DontFetchItem);
    addToWorldState(ActionHelper::Conditions::DontGotoTile);
}

GoalsControllable::~GoalsControllable()
{}

void GoalsControllable::addToWorldState(Condition condition)
{
    for (auto a : mWorldState)
    {
        if (a.first == condition.first)
        {
            a.second = condition.second;
            return;
        }
    }

    mWorldState.insert(condition);
}

PairSet GoalsControllable::getWorldState()
{
    return mWorldState;
}

void GoalsControllable::addToGoalState(Condition condition)
{
    for (auto a : mGoalState)
    {
        if (a.first == condition.first)
        {
            a.second = condition.second;
            return;
        }
    }
    mGoalState.insert(condition);
}

PairSet GoalsControllable::getGoalState()
{
    return mGoalState;
}

void GoalsControllable::onFinished()
{
    emptyGoalState();
}

void GoalsControllable::emptyGoalState()
{
    mGoalState.clear();
}
