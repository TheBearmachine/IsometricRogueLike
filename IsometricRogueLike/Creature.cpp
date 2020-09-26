#include "Creature.h"
#include "Constants.h"
#include "Goals.h"
#include <SFML/System/Time.hpp>

Creature::Creature(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap) :
    Entity(textureName, startTile, currentMap), mGoapAgent(this),
    mMovementComponent(this, Constants::Entities::DefaultTraversalSpeed),
    mOverrideAI(false), mPlayerController(this)
{
    moveToTile(startTile, currentMap);
}

Creature::~Creature()
{
    if (mGoals)
        delete mGoals;
}

void Creature::update(const sf::Time & deltaTime)
{
    if (getGarbage()) return;
    Entity::update(deltaTime);
    if (mOverrideAI)
        mPlayerController.update(deltaTime);
    else
        mGoapAgent.update(this, deltaTime);
}

void Creature::overrideAI(bool doOverride)
{
    mOverrideAI = doOverride;
}

void Creature::setGoals(Goals * goals)
{
    mGoals = goals;
}

Movement * Creature::getMovementComponent()
{
    return &mMovementComponent;
}

GoapAgent * Creature::getGoapAgent()
{
    return &mGoapAgent;
}

CharacterAttributes * Creature::getCharacterAttributes()
{
    return &mCharacterAttributes;
}

Inventory * Creature::getInventory()
{
    return &mInventory;
}

PairSet Creature::getWorldState()
{
    if (mGoals) return mGoals->getWorldState();

    return PairSet();
}

PairSet Creature::createGoalState()
{
    if (mGoals) return mGoals->getGoalState();

    return PairSet();
}

void Creature::planFailed(PairSet failedGoal)
{
}

void Creature::planFound(PairSet goal, std::queue<Action*> actions)
{

}

void Creature::actionsFinished()
{
    if (mGoals) mGoals->onFinished();
}

void Creature::planAborted(Action * aborter)
{
    aborter->doReset();
}

bool Creature::moveAgent(Action * nextAction, const sf::Time& deltaTime)
{
    //bool retVal = true;
    return mMovementComponent.move(deltaTime);

    //retVal = nextAction->getInRange(this);

    //return !mMovementComponent.getMoving();
}
