#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawingManager.h"
#include "ResourceManager.h"
#include "Constants.h"

Entity::Entity(const std::string & textureName) :
	mSprite(ResourceManager::getInstance().getTexture(textureName)),
	mMovementComponent(this, Constants::Entities::DefaultSpeed)
{
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.0f,
					  mSprite.getTextureRect().height - Constants::World::Tile::HalfHeight);
}

Entity::~Entity()
{
}

void Entity::update(const sf::Time & deltaTime)
{
	mMovementComponent.update(deltaTime);
}

void Entity::setPath(std::stack<TileNode*> path)
{
	mMovementComponent.setPath(path);
}

sf::Vector2f Entity::getCurrentMoveTarget() const
{
	return mMovementComponent.getCurrentTarget();
}

void Entity::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mSprite, states);
}
