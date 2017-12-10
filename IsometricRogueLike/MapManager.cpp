#include "MapManager.h"
#include "DrawingManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

MapManager::MapManager()
{

}

MapManager::~MapManager()
{

}

void MapManager::setupMap(const int * tiles, unsigned int width, unsigned int height)
{
	mCurrentMap.setupMap(tiles, width, height);
	mCurrentMap.updateVertexArray(sf::Vector2f(0.0f, 0.0f));
}

Map * MapManager::getCurrentMap()
{
	return &mCurrentMap;
}

void MapManager::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void MapManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mCurrentMap, states);
}

std::stack<TileNode*> MapManager::findPath(const sf::Vector2i & startIndex, const sf::Vector2i & endIndex)
{
	return mCurrentMap.findPath(startIndex, endIndex);
}
