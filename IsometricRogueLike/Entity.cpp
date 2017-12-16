#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawingManager.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Map.h"

static IEntityManager* mEntityManager;

Entity::Entity(const std::string & textureName) :
	mSprite(ResourceManager::getInstance().getTexture(textureName)),
	mGarbage(false),
	mFadeCurrent(0.0f),
	mFadeMax(1.0f)
{
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.0f,
					  mSprite.getTextureRect().height - Constants::World::Tile::HalfHeight);
}

Entity::Entity(const std::string & textureName, const sf::Vector2i & startTile, Map* currentMap) :
	mSprite(ResourceManager::getInstance().getTexture(textureName)),
	mGarbage(false)
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

void Entity::moveToTile(const sf::Vector2i & startTile, Map * currentMap)
{
	if (currentMap)
	{
		Tile* from = currentMap->getTileFromIndex(currentMap->getTileIndexFromCoords(getPosition()));
		Tile* to = currentMap->getTileFromIndex(startTile);

		if (to && !to->getOccupant())
		{
			to->setOccupant(this);
			sf::Vector2f pos = to->getWorldPosCenter();

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

void Entity::remove()
{
	mGarbage = true;
}

bool Entity::getGarbage() const
{
	return mGarbage;
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
