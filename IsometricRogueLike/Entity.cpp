#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawingManager.h"
#include "ResourceManager.h"

Entity::Entity(const std::string & textureName) :
	mSprite(ResourceManager::getInstance().getTexture(textureName))
{
}

Entity::~Entity()
{
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
