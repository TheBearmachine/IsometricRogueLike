#include "Map.h"
#include "ResourceManager.h"
#include "IsometricConversion.h"
#include "TileGraph.h"
#include "Constants.h"
#include "DrawingManager.h"
#include <queue>

#define FloorTileWidth Constants::World::Tile::Width
#define FloorTileHeight Constants::World::Tile::Height
#define WallTileWidth Constants::World::Wall::Width
#define WallTileHeight Constants::World::Wall::Height

static const std::string FLOOR_TILES = Constants::Filepaths::ImagesFolder + "FloorTiles.png";
static const std::string WALL_TILES = Constants::Filepaths::ImagesFolder + "WallTiles.png";

Map::Map()
{
}

Map::~Map()
{
}

void Map::setupMap(const int * tiles, unsigned int width, unsigned int height)
{
	mFloorTex = &ResourceManager::getInstance().getTexture(FLOOR_TILES);
	mWallTex = &ResourceManager::getInstance().getTexture(WALL_TILES);

	mMapWidth = width;
	mMapHeight = height;
	mTiles.clear();

	mFloorVertices.setPrimitiveType(sf::Quads);
	mWallVertices.setPrimitiveType(sf::Quads);

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			int textureID = tiles[i + j * width];
			sf::Vector2f worldPos/* = sf::Vector2f(i * FloorTileWidth, j * FloorTileHeight)*/;
			worldPos = IsometricConversion::toIsometric(sf::Vector2f(i * FloorTileWidth, j * FloorTileWidth));
			worldPos.x -= FloorTileWidth / 2.0f;

			sf::Vector2i arrayIndex(i, j);

			mTiles.push_back(Tile(textureID, worldPos));
			mTiles.back().setArrayIndex(arrayIndex);
		}
	}

	updateTileGraph();
}

void Map::updateVertexArray(const sf::Vector2f cameraPos)
{
	// The int is: 0 no wall attached, 1 a wall to the left, 2 a wall above, 3 if both
	std::vector<std::pair< Tile*, int>> closeTiles;
	size_t walls = 0;

	// Temp solution
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		if (mTiles[i].getTextureID() >= 0)
		{
			int hasAWall = 0;
			// See if the tile texture ID in array position -1 or -mMapWidth is equal to -1
			int left = i - 1;
			int above = i - mMapWidth;
			if (i % mMapWidth == 0 || mTiles[left].getTextureID() == -1)
			{
				hasAWall += 1;
				walls++;
			}
			if (i / mMapWidth == 0 || mTiles[above].getTextureID() == -1)
			{
				hasAWall += 2;
				walls++;
			}

			closeTiles.push_back(std::make_pair(&mTiles[i], hasAWall));
		}
	}

	//TODO: populate closeTiles
	size_t wallCurIndex = 0;

	mFloorVertices.resize((closeTiles.size()) * 4);
	mWallVertices.resize(walls * 4);
	int floorTilemapWidth = (int)mFloorTex->getSize().x;
	int wallTilemapWidth = (int)mWallTex->getSize().x;

	for (size_t i = 0; i < closeTiles.size(); i++)
	{
		int ID = closeTiles[i].first->getTextureID();
		sf::Vertex* quad = &mFloorVertices[i * 4];
		sf::Vector2f tempPos = closeTiles[i].first->getWorldPos();


		int tu = ID % (floorTilemapWidth / (int)FloorTileWidth);
		int tv = ID / (floorTilemapWidth / (int)FloorTileWidth);

		quad[0].position = sf::Vector2f(tempPos.x, tempPos.y);
		quad[1].position = sf::Vector2f(tempPos.x + FloorTileWidth, tempPos.y);
		quad[2].position = sf::Vector2f(tempPos.x + FloorTileWidth, tempPos.y + FloorTileHeight);
		quad[3].position = sf::Vector2f(tempPos.x, tempPos.y + FloorTileHeight);

		quad[0].texCoords = sf::Vector2f(tu * FloorTileWidth, tv * FloorTileHeight);
		quad[1].texCoords = sf::Vector2f((tu + 1) * FloorTileWidth, tv * FloorTileHeight);
		quad[2].texCoords = sf::Vector2f((tu + 1) * FloorTileWidth, (tv + 1) * FloorTileHeight);
		quad[3].texCoords = sf::Vector2f(tu * FloorTileWidth, (tv + 1) * FloorTileHeight);

		ID *= 2;
		if ((closeTiles[i].second & 0b01) == 0b01)
		{
			sf::Vector2f tempPos2 = tempPos;
			tempPos2.x += WallTileWidth;
			tempPos2.y -= WallTileHeight - FloorTileHeight / 2.0f;
			quad = &mWallVertices[wallCurIndex];
			wallCurIndex += 4;

			tu = (ID) % (wallTilemapWidth / (int)WallTileWidth);
			tv = (ID) / (wallTilemapWidth / (int)WallTileWidth);

			quad[0].position = sf::Vector2f(tempPos2.x, tempPos2.y);
			quad[1].position = sf::Vector2f(tempPos2.x + WallTileWidth, tempPos2.y);
			quad[2].position = sf::Vector2f(tempPos2.x + WallTileWidth, tempPos2.y + WallTileHeight);
			quad[3].position = sf::Vector2f(tempPos2.x, tempPos2.y + WallTileHeight);

			quad[0].texCoords = sf::Vector2f(tu * WallTileWidth, tv * WallTileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * WallTileWidth, tv * WallTileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * WallTileWidth, (tv + 1) * WallTileHeight);
			quad[3].texCoords = sf::Vector2f(tu * WallTileWidth, (tv + 1) * WallTileHeight);
		}

		int test = closeTiles[i].second & 0b10;
		if ((closeTiles[i].second & 0b10) == 0b10)
		{
			sf::Vector2f tempPos2 = tempPos;
			tempPos2.y -= WallTileHeight - FloorTileHeight / 2.0f;
			quad = &mWallVertices[wallCurIndex];
			wallCurIndex += 4;

			tu = (ID + 1) % (wallTilemapWidth / (int)WallTileWidth);
			tv = (ID + 1) / (wallTilemapWidth / (int)WallTileWidth);

			quad[0].position = sf::Vector2f(tempPos2.x, tempPos2.y);
			quad[1].position = sf::Vector2f(tempPos2.x + WallTileWidth, tempPos2.y);
			quad[2].position = sf::Vector2f(tempPos2.x + WallTileWidth, tempPos2.y + WallTileHeight);
			quad[3].position = sf::Vector2f(tempPos2.x, tempPos2.y + WallTileHeight);

			quad[0].texCoords = sf::Vector2f(tu * WallTileWidth, tv * WallTileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * WallTileWidth, tv * WallTileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * WallTileWidth, (tv + 1) * WallTileHeight);
			quad[3].texCoords = sf::Vector2f(tu * WallTileWidth, (tv + 1) * WallTileHeight);
		}
	}
}

sf::Vector2i Map::getTileIndexFromCoords(const sf::Vector2f & coords)
{
	return IsometricConversion::fromIsometricTile(coords);
}

void Map::updateTileGraph()
{
	mTileGraph.clearNodes();

	for (size_t i = 0; i < mTiles.size(); i++)
	{
		TileNode node;
		node.mTile = &mTiles[i];
		node.mAccumulatedCost = -1;
		mTileGraph.addTileNode(node);
	}

	for (size_t i = 0; i < mTiles.size(); i++)
	{
		if (mTiles[i].getTextureID() != -1)
		{
			TileNode* node = mTileGraph.getNode(i);

			int right = i + 1;
			int down = i + mMapWidth;
			int left = i - 1;
			int up = i - mMapWidth;

			// Populate Neighbors
			// Right
			if (i % mMapWidth != mMapWidth - 1 && mTiles[right].getTextureID() != -1)
				node->mNeighbors[TileNode::Neightbor::Right] = mTileGraph.getNode(&mTiles[right]);

			// Down
			if (i / mMapWidth != mMapHeight - 1 && mTiles[down].getTextureID() != -1)
				node->mNeighbors[TileNode::Neightbor::Down] = mTileGraph.getNode(&mTiles[down]);

			// Left
			if (i % mMapWidth != 0 && mTiles[left].getTextureID() != -1)
				node->mNeighbors[TileNode::Neightbor::Left] = mTileGraph.getNode(&mTiles[left]);

			// Up
			if (i / mMapWidth != 0 && mTiles[up].getTextureID() != -1)
				node->mNeighbors[TileNode::Neightbor::Up] = mTileGraph.getNode(&mTiles[up]);

		}
	}
}

bool containsElement(std::priority_queue<TileNode*, std::vector<TileNode*>, CompareTileNodeCosts> queue, TileNode* element)
{
	while (!queue.empty())
	{
		TileNode* temp = queue.top();
		if (temp == element) return true;
		queue.pop();
	}
	return false;
}

template <typename T>
bool containsElement(const std::vector<T*> &vector, T* element)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == element)
			return true;
	}
	return false;
}

std::stack<TileNode*> Map::findPath(const sf::Vector2i & startIndex, const sf::Vector2i & endIndex)
{
	std::vector<TileNode*>closedList;
	std::stack<TileNode*> finalPath;
	std::priority_queue<TileNode*, std::vector<TileNode*>, CompareTileNodeCosts> openList;
	TileNode *startTile = mTileGraph.getNode(&mTiles[startIndex.x + startIndex.y * mMapWidth]),
		*finalTile = nullptr;
	if (!startTile) return std::stack<TileNode*>();

	startTile->mAccumulatedCost = 0;
	startTile->mParent = nullptr;
	bool done = false;

	openList.push(startTile);
	TileNode* neighbor;

	while (!done && !openList.empty())
	{
		auto currentTile = openList.top();
		openList.pop();
		closedList.push_back(currentTile);

		// Expand all neighboring tiles
		for (int i = 0; i < 4; i++)
		{

			neighbor = currentTile->mNeighbors[i];

			if (neighbor != nullptr && neighbor->mTile->getArrayIndex() == endIndex)
			{
				neighbor->mParent = currentTile;
				finalTile = neighbor;
				done = true;
			}
			else if (neighbor != nullptr &&
					 !containsElement(closedList, neighbor) &&
					 !containsElement(openList, neighbor))
			{
				int manhattanDist = abs(currentTile->mTile->getArrayIndex().x - neighbor->mTile->getArrayIndex().x)
					+ abs(currentTile->mTile->getArrayIndex().y - neighbor->mTile->getArrayIndex().y);
				int cost = currentTile->mAccumulatedCost + manhattanDist + 1;

				neighbor->mAccumulatedCost = cost;
				neighbor->mParent = currentTile;
				openList.push(neighbor);
			}
		}
	}
	if (finalTile == nullptr)
	{
		printf("No path found!\n", finalPath.size());
		return std::stack<TileNode*>();
	}
	auto currentTile = finalTile;
	while (currentTile->mParent)
	{
		finalPath.push(currentTile);
		currentTile = currentTile->mParent;
	}
	printf("Final list size: %i\n", finalPath.size());
	printf("Closed list size: %i\n", closedList.size());

	return finalPath;
}

void Map::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	states.texture = mFloorTex;
	target.draw(mFloorVertices, states);
	states.texture = mWallTex;
	target.draw(mWallVertices, states);
}
