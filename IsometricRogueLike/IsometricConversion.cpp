#include "IsometricConversion.h"
#include "Constants.h"

#define TileHalfWidth Constants::World::Tile::HalfWidth
#define TileHalfHeight Constants::World::Tile::HalfHeight

sf::Vector2f IsometricConversion::toIsometric(const sf::Vector2f & vec)
{
	sf::Vector2f v;
	v.x = (vec.x - vec.y) * 0.5f;
	v.y = (vec.x + vec.y) * 0.3125f;

	return v;
}

sf::Vector2f IsometricConversion::fromIsometric(const sf::Vector2f & vec)
{
	sf::Vector2f v;
	v.x = (vec.x / 0.5f + vec.y / 0.3125f) / 2.0f;
	v.y = ((vec.y / 0.3125f) - (vec.x / 0.5f)) / 2.0f;

	return v;
}

sf::Vector2i IsometricConversion::fromIsometricTile(const sf::Vector2f & vec)
{
	sf::Vector2i v;
	v.x = (vec.x / TileHalfWidth + vec.y / TileHalfHeight) / 2.0f;
	v.y = (vec.y / TileHalfHeight - (vec.x / TileHalfWidth)) / 2.0f;

	return v;
}
