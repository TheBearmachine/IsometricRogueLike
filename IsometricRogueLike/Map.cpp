#include "Map.h"
#include "ResourceManager.h"
#include "IsometricConversion.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

#define TileWidth Constants::World::Tile::Width
#define TileHeight Constants::World::Tile::Height

Map::Map()
{
}

Map::~Map()
{
}

void Map::setupMap(const std::string & tileset, const int * tiles, unsigned int width, unsigned int height)
{
	mTilemapTex = &ResourceManager::getInstance().getTexture(tileset);
	mMapWidth = width;
	mMapHeight = height;
	mTiles.clear();

	mVertices.setPrimitiveType(sf::Quads);

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			int textureID = tiles[i + j * width];
			sf::Vector2f worldPos = IsometricConversion::toIsometric(sf::Vector2f(i * TileWidth, j * TileWidth));

			mTiles.push_back(Tile(textureID, worldPos));
		}
	}
}

void Map::updateVertexArray(const sf::Vector2f cameraPos)
{
	std::vector<Tile*> closeTiles;

	// Temp solution
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		if (mTiles[i].getTextureID() >= 0)
			closeTiles.push_back(&mTiles[i]);
	}

	//TODO: populate closeTiles


	mVertices.resize(closeTiles.size() * 4);
	int tilemapWidth = (int)mTilemapTex->getSize().x;
	int tilemapHeight = (int)mTilemapTex->getSize().y;

	for (size_t i = 0; i < closeTiles.size(); i++)
	{
		int ID = closeTiles[i]->getTextureID();
		sf::Vertex* quad = &mVertices[i * 4];
		sf::Vector2f tempPos = closeTiles[i]->getWorldPos();


		int tu = ID % (tilemapWidth / (int)TileWidth);
		int tv = ID / (tilemapWidth / (int)TileWidth);

		quad[0].position = sf::Vector2f(tempPos.x, tempPos.y);
		quad[1].position = sf::Vector2f(tempPos.x + TileWidth, tempPos.y);
		quad[2].position = sf::Vector2f(tempPos.x + TileWidth, tempPos.y + TileHeight);
		quad[3].position = sf::Vector2f(tempPos.x, tempPos.y + TileHeight);

		quad[0].texCoords = sf::Vector2f(tu * TileWidth, tv * TileHeight);
		quad[1].texCoords = sf::Vector2f((tu + 1) * TileWidth, tv * TileHeight);
		quad[2].texCoords = sf::Vector2f((tu + 1) * TileWidth, (tv + 1) * TileHeight);
		quad[3].texCoords = sf::Vector2f(tu * TileWidth, (tv + 1) * TileHeight);
	}
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.texture = mTilemapTex;
	target.draw(mVertices, states);
}
