#include "IsometricConversion.h"
#include "Constants.h"

#define TileHalfWidth Constants::World::Tile::HalfWidth
#define TileHalfHeight Constants::World::Tile::HalfHeight

sf::Vector2f IsometricConversion::toIsometric(const sf::Vector2f & vec)
{
	sf::Vector2f v;
	v.x = (vec.x - vec.y) * TileHalfWidth;
	v.y = (vec.x + vec.y) * TileHalfHeight;

	return v;
}

sf::Vector2f IsometricConversion::fromIsometric(const sf::Vector2f & vec)
{
	sf::Vector2f v;
	v.x = (vec.x / TileHalfWidth + vec.y / TileHalfHeight) / 2.0f;
	v.y = ((vec.y / TileHalfWidth) - (vec.x / TileHalfHeight)) / 2.0f;

	return sf::Vector2f();
}
