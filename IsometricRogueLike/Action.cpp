#include "Action.h"

static Map* mCurrentMap;

Action::Action(ActionTypes actionType) :
    mCost(1.0f), mActionType(actionType),
    mTargetEntity(nullptr), mTargetItem(nullptr)
{

}

Action::~Action()
{

}

bool Action::planPath(Entity * self)
{
    return true;
}

void Action::setCost(float newCost)
{
    mCost = newCost;
}

float Action::getCost() const
{
    return mCost;
}

void Action::setInRange(bool inRange)
{
    mInRange = inRange;
}

bool Action::getInRange(Entity* self) const
{
    return mInRange;
}

void Action::addPrecondition(const std::string &key, size_t val)
{
    mPreconditions.insert(std::make_pair(key, val));
}

void Action::addPrecondition(const Condition & cond)
{
    addPrecondition(cond.first, cond.second);
}

void Action::removePrecondition(const std::string &key, size_t val)
{
    auto temp = std::make_pair(key, val);
    mPreconditions.erase(temp);
}

const PairSet& Action::getPreconditions() const
{
    return mPreconditions;
}

void Action::addEffect(const std::string & key, size_t val)
{
    mEffects.insert(std::make_pair(key, val));
}

void Action::addEffect(const Condition & cond)
{
    addEffect(cond.first, cond.second);
}

void Action::removeEffect(const std::string &key, size_t val)
{
    auto temp = std::make_pair(key, val);
    mEffects.erase(temp);
}

const PairSet& Action::getEffects() const
{
    return mEffects;
}

Action::ActionTypes Action::getActionType() const
{
    return mActionType;
}

void Action::setTargetEntity(Entity * target)
{
    mTargetEntity = target;
}

Entity * Action::getTargetEntity() const
{
    return mTargetEntity;
}

void Action::setTargetItem(Item * target)
{
    mTargetItem = target;
}

Item * Action::getTargetItem() const
{
    return mTargetItem;
}

void Action::doReset()
{
    mInRange = false;
    mTargetEntity = nullptr;
    mTargetItem = nullptr;
}

void Action::setCurrentMap(Map * currentMap)
{
    mCurrentMap = currentMap;
}

Map * Action::getCurrentMap()
{
    return mCurrentMap;
}
