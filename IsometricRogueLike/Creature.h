#pragma once
#include "Entity.h"
#include "Movement.h"
#include "GoapAgent.h"
#include "CharacterAttributes.h"
#include "AnimationSystem.h"
#include "PlayerController.h"
#include "Inventory.h"

class ControlSystem;
class Goals;

class Creature : public Entity
{
public:
    Creature(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
    ~Creature();

    virtual void update(const sf::Time &deltaTime) override;

    void overrideAI(bool doOverride);
    void setGoals(Goals* goals);

    virtual Movement* getMovementComponent() override;
    virtual GoapAgent* getGoapAgent() override;

    virtual CharacterAttributes* getCharacterAttributes() override;
    virtual Inventory* getInventory() override;

   //virtual void addToGoalState(Condition goal) override;
    virtual PairSet getWorldState() override;
    virtual PairSet createGoalState() override;

    virtual void planFailed(PairSet failedGoal) override;
    virtual void planFound(PairSet goal, std::queue<Action*> actions) override;
    virtual void actionsFinished() override;
    virtual void planAborted(Action* aborter) override;
    virtual bool moveAgent(Action* nextAction, const sf::Time& deltaTime) override;

private:
    Movement mMovementComponent;
    GoapAgent mGoapAgent;
    PlayerController mPlayerController;
    Goals* mGoals;

    CharacterAttributes mCharacterAttributes;
    Inventory mInventory;

    bool mOverrideAI;

};