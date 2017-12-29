#pragma once
#include "DrawThis.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Tile.h"
#include "TileGraph.h"
#include <vector>
#include <stack>
#include <unordered_set>

class TileGraph;
namespace sf
{
	class Time;
}

class Map : public DrawThis
{
public:
	Map();
	~Map();

	void setupMap(const int* tiles, unsigned int width, unsigned int height);
	void updateVertexArray(const sf::Vector2f worldPos, int distance, int duration);

	sf::Vector2i getTileIndexFromCoords(const sf::Vector2f &coords);
	Tile* getTileFromIndex(const sf::Vector2i index);

	void update(const sf::Time &deltaTime);

	void updateTileGraph();
	std::stack<TileNode*> findPath(const sf::Vector2i &startIndex, const sf::Vector2i &endIndex);

	bool lineOfSight(const sf::Vector2f &p1, const sf::Vector2f &p2, float stepSize = 10.0f);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray mFloorVertices;
	sf::Texture *mFloorTex;
	sf::VertexArray mWallVertices;
	sf::Texture *mWallTex;
	std::vector<std::pair< size_t, Tile*>> mDarkFloorIndices;
	std::vector<std::pair< size_t, Tile*>> mDarkWallIndices;

	std::vector<Tile> mTiles;

	TileGraph mTileGraph;

	unsigned int mMapWidth;
	unsigned int mMapHeight;
};