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

	void drawPrep(DrawingManager* drawingMan) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Time &deltaTime);
	//std::stack<TileNode*> findPath(const sf::Vector2i & startIndex, const sf::Vector2i & endIndex);

private:
	Map mCurrentMap;
};