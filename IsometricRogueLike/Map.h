#pragma once
#include "DrawThis.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Tile.h"
#include <vector>

class Map : public DrawThis
{
public:
	Map();
	~Map();

	void setupMap(const int* tiles, unsigned int width, unsigned int height);
	void updateVertexArray(const sf::Vector2f cameraPos);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray mFloorVertices;
	sf::Texture *mFloorTex;
	sf::VertexArray mWallVertices;
	sf::Texture *mWallTex;

	std::vector<Tile> mTiles;
	unsigned int mMapWidth;
	unsigned int mMapHeight;
};