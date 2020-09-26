#pragma once
#include "DrawThis.h"
#include "Transformabetter.h"
#include "IEntityManager.h"
#include "Action.h"
#include "AnimationSystem.h"
#include "IGoap.h"
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Map;
class Action;
class GoapAgent;
class FSMHandler;
class Movement;
class CharacterAttributes;
class Inventory;
namespace sf
{
    class Time;
}

class Entity : public DrawThis, public Transformabetter, public IGoap
{
public:
    //Entity(const std::string &textureName);
    Entity(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
    ~Entity();

    virtual void update(const sf::Time &deltaTime);

    void setDoesTick(bool tick);
    bool getDoesTick() const;

    void moveToTile(const sf::Vector2i & startTile, Map* currentMap);

    virtual AnimationSystem* getAnimationsystemComponent();
    virtual Movement* getMovementComponent();

    virtual CharacterAttributes* getCharacterAttributes();
    virtual Inventory* getInventory();

    sf::Sprite* getSprite();

    void remove();
    bool getGarbage() const;

    void setAlive(bool isAlive);
    bool getAlive() const;

    void setFadeMax(float val);
    void reduceFadeCurrent(float deltaVal);
    float getFadeRatio() const;

    AnimationNode* addAnimationNode(AnimationTransformBased::AnimationTransformType type);

    virtual void drawPrep(DrawingManager* drawingMan);
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

    static void setup(IEntityManager* entityManager);
    IEntityManager* getEntityManager();

    virtual PairSet getWorldState() override;
    virtual PairSet createGoalState() override;
    virtual void addToGoalState(Condition goal) override;

    virtual void planFailed(PairSet failedGoal) override;
    virtual void planFound(PairSet goal, std::queue<Action*> actions) override;
    virtual void actionsFinished() override;
    virtual void planAborted(Action* aborter) override;
    virtual bool moveAgent(Action* nextAction, const sf::Time& deltaTime) override;

    virtual GoapAgent* getGoapAgent();

protected:
    sf::Sprite mSprite;
    AnimationSystem mAnimationSystem;

private:
    //PairSet mGoalState;
    bool mGarbage;
    bool mAlive;
    bool mTick;
    float mFadeMax, mFadeCurrent;
};