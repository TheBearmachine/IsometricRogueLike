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
{
}

void Entity::update(const sf::Time & deltaTime)
{
	reduceFadeCurrent(deltaTime.asSeconds());
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

FSMAction * Entity::getFSMActionComponent()
{
	return nullptr;
}

FSMIdle * Entity::getFSMIdleComponent()
{
	return nullptr;
}

FSM * Entity::getCurrentFSMState()
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

void Entity::addAvailableAction(Action::ActionTypes actionType)
{
	mAvailableActions.push_back(actionType);
}

const std::vector<Action::ActionTypes>& Entity::getAvailableActions() const
{
	return mAvailableActions;
}

void Entity::setWorldState(const std::string & key, size_t val)
{
	mWorldState[key] = val;
}

const Action::WorldState & Entity::getWorldState() const
{
	return mWorldState;
}

void Entity::drawPrep(DrawingManager * drawingMan)
{
	if (mGarbage) return;
	setZBuffer((int)getPosition().y);
	int colorVal = (int)(getFadeRatio() * 255.0f);
	mSprite.setColor(sf::Color(255, 255, 255, colorVal));
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
