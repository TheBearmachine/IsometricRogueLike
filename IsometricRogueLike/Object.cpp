#include "Object.h"
#include "Constants.h"

Object::Object(const std::string & textureName, const sf::Vector2i & startTile, Map* currentMap) :
	Entity(textureName, startTile, currentMap)
{
	sf::Vector2f ori = mSprite.getOrigin();
	ori.y -= Constants::World::Tile::HalfHeight;
	mSprite.setOrigin(ori);
}

Object::~Object()
{

}

void Object::update(const sf::Time & deltaTime)
{
	Entity::update(deltaTime);
}
