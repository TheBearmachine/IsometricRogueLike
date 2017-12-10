#pragma once
#include "DrawThis.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Tile.h"
#include "TileGraph.h"
#include <vector>
#include <stack>

class TileGraph;

class Map : public DrawThis
{
public:
	Map();
	~Map();

	void setupMap(const int* tiles, unsigned int width, unsigned int height);
	void updateVertexArray(const sf::Vector2f cameraPos);

	sf::Vector2i getTileIndexFromCoords(const sf::Vector2f &coords);

	void updateTileGraph();
	std::stack<TileNode*> findPath(const sf::Vector2i &startIndex, const sf::Vector2i &endIndex);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray mFloorVertices;
	sf::Texture *mFloorTex;
	sf::VertexArray mWallVertices;
	sf::Texture *mWallTex;

	std::vector<Tile> mTiles;
	TileGraph mTileGraph;

	unsigned int mMapWidth;
	unsigned int mMapHeight;
};