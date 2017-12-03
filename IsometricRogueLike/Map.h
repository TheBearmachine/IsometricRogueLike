#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Tile.h"
#include <vector>

class Map : public sf::Drawable
{
public:
	Map();
	~Map();

	void setupMap(const std::string &tileset, const int* tiles, unsigned int width, unsigned int height);
	void updateVertexArray(const sf::Vector2f cameraPos);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray mVertices;
	sf::Texture *mTilemapTex;

	std::vector<Tile> mTiles;
	unsigned int mMapWidth;
	unsigned int mMapHeight;
};