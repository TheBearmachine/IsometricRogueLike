#include "Creature.h"
#include "Constants.h"

Creature::Creature(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap) :
	Entity(textureName, startTile, currentMap),
	mFSMAction(&mCurrentState, this), mFSMIdle(&mCurrentState),
	mMovementComponent(this, Constants::Entities::DefaultTraversalSpeed, &mCurrentState)
{
	mCurrentState = &mMovementComponent;
	mMovementComponent.setFSMAction(&mFSMAction);
	mMovementComponent.setFSMIdle(&mFSMIdle);
	mFSMAction.setFSMIdle(&mFSMIdle);
	mFSMAction.setFSMMove(&mMovementComponent);
	mFSMIdle.setFSMMove(&mMovementComponent);
	mFSMIdle.setFSMAction(&mFSMAction);
	moveToTile(startTile, currentMap);
}

Creature::~Creature()
{

}

void Creature::update(const sf::Time & deltaTime)
{
	if (getGarbage()) return;
	Entity::update(deltaTime);
	mCurrentState->update(deltaTime);
}

FSMMove * Creature::getMovementComponent()
{
	return &mMovementComponent;
}

FSMAction * Creature::getFSMActionComponent()
{
	return &mFSMAction;
}

FSMIdle * Creature::getFSMIdleComponent()
{
	return &mFSMIdle;
}

FSM * Creature::getCurrentFSMState()
{
	return mCurrentState;
}

CharacterAttributes * Creature::getCharacterAttributes()
{
	return &mCharacterAttributes;
}

Inventory * Creature::getInventory()
{
	return &mInventory;
}
