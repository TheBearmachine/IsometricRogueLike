#pragma once
#include "Map.h"
#include "TileGraph.h"
#include "DrawThis.h"

class MapManager: public DrawThis
{
public:
	MapManager();
	~MapManager();

	void setupMap(const int * tiles, unsigned int width, unsigned int height);
	Map* getCurrentMap();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::stack<TileNode*> findPath(const sf::Vector2i & startIndex, const sf::Vector2i & endIndex);

private:
	Map mCurrentMap;
};