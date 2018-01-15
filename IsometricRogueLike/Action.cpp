#include "Action.h"

static Map* mCurrentMap;

Action::Action() :
	mCost(1.0f)
{

}

Action::~Action()
{

}

void Action::setCost(float newCost)
{
	mCost = newCost;
}

float Action::getCost() const
{
	return mCost;
}

void Action::addPrecondition(const std::string &key, size_t val)
{
	mPreconditions[key] = val;
}

void Action::removePrecondition(const std::string & key)
{
	mPreconditions.erase(key);
}

const Action::WorldState& Action::getPreconditions() const
{
	return mPreconditions;
}

void Action::addEffect(const std::string & key, size_t val)
{
	mEffects[key] = val;
}

void Action::removeEffect(const std::string & key)
{
	mEffects.erase(key);
}

const Action::WorldState & Action::getEffects() const
{
	return mEffects;
}

void Action::setCurrentMap(Map * currentMap)
{
	mCurrentMap = currentMap;
}

Map * Action::getCurrentMap()
{
	return mCurrentMap;
}
