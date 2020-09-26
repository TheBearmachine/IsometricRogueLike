#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawingManager.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Map.h"

static IEntityManager* mEntityManager;

//Entity::Entity(const std::string & textureName) :
//	mSprite(ResourceManager::getInstance().getTexture(textureName)),
//	mGarbage(false), mAlive(true),
//	mTick(true),
//	mFadeCurrent(0.0f),
//	mFadeMax(1.0f)
//{
//	mSprite.setOrigin(mSprite.getTextureRect().width / 2.0f,
//					  mSprite.getTextureRect().height - Constants::World::Tile::HalfHeight);
//}

Entity::Entity(const std::string & textureName, const sf::Vector2i & startTile, Map* currentMap) :
    mSprite(ResourceManager::getInstance().getTexture(textureName)),
    mGarbage(false), mAlive(true),
    mTick(true),
    mFadeCurrent(0.0f), mFadeMax(1.0f)
{
    mSprite.setOrigin(mSprite.getTextureRect().width / 2.0f,
                      mSprite.getTextureRect().height - Constants::World::Tile::HalfHeight);

    moveToTile(startTile, currentMap);
}

Entity::~Entity()
{}

void Entity::update(const sf::Time & deltaTime)
{
    //reduceFadeCurrent(deltaTime.asSeconds());
    mAnimationSystem.update(deltaTime);
}

void Entity::setDoesTick(bool tick)
{
    mTick = tick;
}

bool Entity::getDoesTick() const
{
    return mTick;
}

void Entity::moveToTile(const sf::Vector2i & startTile, Map * currentMap)
{
    if (currentMap)
    {
        Tile* from = currentMap->getTileFromIndex(currentMap->getTileIndexFromCoords(getPosition()));
        Tile* to = currentMap->getTileFromIndex(startTile);

        if (to && !to->getOccupant())
        {
            to->setOccupant(this);
            sf::Vector2f pos = to->getPosition();

            setPosition(pos);
            if (from && from->getOccupant() == this)
                from->setOccupant(nullptr);
        }
    }
}

Movement * Entity::getMovementComponent()
{
    return nullptr;
}

CharacterAttributes * Entity::getCharacterAttributes()
{
    return nullptr;
}

Inventory * Entity::getInventory()
{
    return nullptr;
}

sf::Sprite * Entity::getSprite()
{
    return &mSprite;
}

void Entity::remove()
{
    mGarbage = true;
}

bool Entity::getGarbage() const
{
    return mGarbage;
}

void Entity::setAlive(bool isAlive)
{
    mAlive = isAlive;
}

bool Entity::getAlive() const
{
    return mAlive;
}

void Entity::setFadeMax(float val)
{
    mFadeCurrent = mFadeMax = val;
}

void Entity::reduceFadeCurrent(float deltaVal)
{
    mFadeCurrent = std::fmaxf(0.0f, mFadeCurrent - deltaVal);
}

float Entity::getFadeRatio() const
{
    return mFadeCurrent / mFadeMax;
}

AnimationNode* Entity::addAnimationNode(AnimationTransformBased::AnimationTransformType type)
{
    return mAnimationSystem.addNode(type, &mSprite);
}

AnimationSystem * Entity::getAnimationsystemComponent()
{
    return &mAnimationSystem;
}

void Entity::drawPrep(DrawingManager * drawingMan)
{
    if (mGarbage) return;
    setZBuffer((int)getPosition().y);
    int colorVal = (int)(getFadeRatio() * 255.0f);
    mSprite.setColor(sf::Color(colorVal, colorVal, colorVal, 255.0f));
    drawingMan->addDrawable(this);
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform = getGlobalTransform();
    target.draw(mSprite, states);
}

void Entity::setup(IEntityManager * entityManager)
{
    mEntityManager = entityManager;
}

IEntityManager * Entity::getEntityManager()
{
    return mEntityManager;
}

PairSet Entity::getWorldState()
{
    return PairSet();
}

PairSet Entity::createGoalState()
{
    return PairSet();
}

void Entity::addToGoalState(Condition goal)
{}

void Entity::planFailed(PairSet failedGoal)
{}

void Entity::planFound(PairSet goal, std::queue<Action*> actions)
{}

void Entity::actionsFinished()
{}

void Entity::planAborted(Action * aborter)
{}

bool Entity::moveAgent(Action * nextAction, const sf::Time& deltaTime)
{
    return false;
}

GoapAgent * Entity::getGoapAgent()
{
    return nullptr;
}
