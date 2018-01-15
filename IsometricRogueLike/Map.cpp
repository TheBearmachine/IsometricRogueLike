#include "Map.h"
#include "ResourceManager.h"
#include "IsometricConversion.h"
#include "TileGraph.h"
#include "Constants.h"
#include "DrawingManager.h"
#include "VectorFunctions.h"
#include "Item.h"
#include <queue>
#include <SFML/System/Time.hpp>

#define FloorTileWidth Constants::World::Tile::Width
#define FloorTileHeight Constants::World::Tile::Height
#define WallTileWidth Constants::World::Wall::Width
#define WallTileHeight Constants::World::Wall::Height

static const std::string FLOOR_TILES = Constants::Filepaths::ImagesFolder + "FloorTiles.png";
static const std::string WALL_TILES = Constants::Filepaths::ImagesFolder + "WallTiles.png";

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

void Map::updateVertexArray(const sf::Vector2f worldPos, int distance, int duration)
{

	// The int is: 0 no wall attached, 1 a wall to the left, 2 a wall above, 3 if both
	std::vector<std::pair< Tile*, int>> visibleTiles;
	size_t walls = 0;
	size_t floorTiles = 0;

	mDarkFloorIndices.clear();
	mDarkWallIndices.clear();
	// Find visible tiles
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		if (mTiles[i].getTextureID() >= 0)
		{
			sf::Vector2f tilePos = mTiles[i].getPosition();
			tilePos.y += Constants::World::Tile::HalfHeight;
			int distFromPosSq = (int)VectorFunctions::vectorMagnitudeSquared(tilePos - worldPos);
			bool tooFar = distFromPosSq > distance * distance;
			if (tooFar)
			{
				mDarkFloorIndices.push_back(std::make_pair(floorTiles, &mTiles[i]));
			}
			else if (!lineOfSight(tilePos, worldPos, 20.0f))
			{
				mDarkFloorIndices.push_back(std::make_pair(floorTiles, &mTiles[i]));
			}
			else
				mTiles[i].setFadeMax((float)duration);


			floorTiles++;
			int hasAWall = 0;
			// See if the tile texture ID in array position -1 or -mMapWidth is equal to -1
			int left = i - 1;
			int above = i - mMapWidth;
			if (i % mMapWidth == 0 || mTiles[left].getTextureID() == -1)
			{
				hasAWall += 1;
				if (tooFar)
					mDarkWallIndices.push_back(std::make_pair(walls, &mTiles[i]));
				walls++;
			}
			if (i / mMapWidth == 0 || mTiles[above].getTextureID() == -1)
			{
				hasAWall += 2;
				if (tooFar)
					mDarkWallIndices.push_back(std::make_pair(walls, &mTiles[i]));
				walls++;
			}
			visibleTiles.push_back(std::make_pair(&mTiles[i], hasAWall));
		}
	}

	size_t wallCurIndex = 0;

	mFloorVertices.resize(visibleTiles.size() * 4);
	mWallVertices.resize(walls * 4);
	int floorTilemapWidth = (int)mFloorTex->getSize().x;
	int wallTilemapWidth = (int)mWallTex->getSize().x;

	for (size_t i = 0; i < visibleTiles.size(); i++)
	{
		int ID = visibleTiles[i].first->getTextureID();
		sf::Vertex* quad = &mFloorVertices[i * 4];
		sf::Vector2f tempPos = visibleTiles[i].first->getWorldPos();
		int colorVal = (int)(visibleTiles[i].first->getFadeRatio() * 255.0f);

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

		quad[0].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[1].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[2].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[3].color = sf::Color(colorVal, colorVal, colorVal, 255);

		for (auto it : visibleTiles[i].first->getItems())
			it->getSprite()->setColor(sf::Color(255, 255, 255, colorVal));

		ID *= 2;
		if ((visibleTiles[i].second & 0b01) == 0b01)
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

			quad[0].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[1].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[2].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[3].color = sf::Color(colorVal, colorVal, colorVal, 255);
		}

		if ((visibleTiles[i].second & 0b10) == 0b10)
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

			quad[0].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[1].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[2].color = sf::Color(colorVal, colorVal, colorVal, 255);
			quad[3].color = sf::Color(colorVal, colorVal, colorVal, 255);
		}
	}
}

sf::Vector2i Map::getTileIndexFromCoords(const sf::Vector2f & coords)
{
	return IsometricConversion::fromIsometricTile(coords);
}

Tile * Map::getTileFromIndex(const sf::Vector2i index)
{
	if (index.x >= (int)mMapWidth ||
		index.x < 0 ||
		index.y >= (int)mMapHeight ||
		index.y < 0) return nullptr;
	return &mTiles[index.y + index.x * mMapWidth];
}

void Map::update(const sf::Time & deltaTime)
{
	for (size_t i = 0; i < mDarkFloorIndices.size(); i++)
	{
		mDarkFloorIndices[i].second->reduceFadeCurrent(deltaTime.asSeconds());
		int colorVal = (int)(mDarkFloorIndices[i].second->getFadeRatio() * 255.0f);
		sf::Vertex* quad = &mFloorVertices[mDarkFloorIndices[i].first * 4];

		for (auto it : mDarkFloorIndices[i].second->getItems())
			it->getSprite()->setColor(sf::Color(255, 255, 255, colorVal));

		quad[0].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[1].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[2].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[3].color = sf::Color(colorVal, colorVal, colorVal, 255);
	}

	for (size_t i = 0; i < mDarkWallIndices.size(); i++)
	{
		int colorVal = (int)(mDarkWallIndices[i].second->getFadeRatio() * 255.0f);
		sf::Vertex* quad = &mWallVertices[mDarkWallIndices[i].first * 4];

		quad[0].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[1].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[2].color = sf::Color(colorVal, colorVal, colorVal, 255);
		quad[3].color = sf::Color(colorVal, colorVal, colorVal, 255);
	}
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

size_t Map::findPath(const sf::Vector2i & startIndex, const sf::Vector2i & endIndex, std::stack<TileNode*> &outPath)
{
	while (!outPath.empty())
		outPath.pop();

	size_t pathExists = 1;
	int startI = startIndex.y + startIndex.x * mMapWidth,
		endI = endIndex.y + endIndex.x * mMapWidth;
	if (startI >= (int)mTiles.size() || startI < 0 ||
		endI >= (int)mTiles.size() || endI < 0 ||
		endIndex.x >= (int)mMapWidth || endIndex.x < 0 ||
		endIndex.y >= (int)mMapHeight || endIndex.y < 0)
	{
		printf("Target out of bounds!\n");
		return false;
	}

	std::vector<TileNode*>closedList;
	std::stack<TileNode*> finalPath;
	std::priority_queue<TileNode*, std::vector<TileNode*>, CompareTileNodeCosts> openList;
	TileNode *startTile = mTileGraph.getNode(&mTiles[startI]),
		*finalTile = mTileGraph.getNode(&mTiles[endI]);

	if (!startTile || startTile == finalTile)
	{
		printf("Start same as goal.\n");
		return true;
	}

	int manhattanDist =
		abs(finalTile->mTile->getArrayIndex().x - startTile->mTile->getArrayIndex().x) +
		abs(finalTile->mTile->getArrayIndex().y - startTile->mTile->getArrayIndex().y);

	startTile->mAccumulatedCost = 0;
	startTile->mDistanceFromTarget = manhattanDist;

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

			if (neighbor)
			{
				if (neighbor->mTile->getOccupant() != nullptr)
				{
					if (neighbor->mTile->getArrayIndex() == endIndex)
					{
						neighbor->mParent = currentTile;
						finalTile = neighbor;
						done = true;
						pathExists = 2;
					}
					else
						continue;
				}

				if (neighbor->mTile->getArrayIndex() == endIndex)
				{
					neighbor->mParent = currentTile;
					//finalTile = neighbor;
					done = true;
				}
				else if (!containsElement(closedList, neighbor) &&
						 !containsElement(openList, neighbor))
				{
					manhattanDist =
						abs(finalTile->mTile->getArrayIndex().x - neighbor->mTile->getArrayIndex().x) +
						abs(finalTile->mTile->getArrayIndex().y - neighbor->mTile->getArrayIndex().y);
					int cost = currentTile->mAccumulatedCost + manhattanDist + 1;

					neighbor->mAccumulatedCost = cost;
					neighbor->mDistanceFromTarget = manhattanDist;
					neighbor->mParent = currentTile;
					openList.push(neighbor);
				}
			}
		}
	}

	auto currentTile = finalTile;
	if (!done)
	{
		printf("No path found! Will use the tile with the lowest cost.\n");
		pathExists = 0;
		size_t nearest = 0;
		int currentLowest = 1000;
		for (size_t i = 0; i < closedList.size(); i++)
		{
			if (closedList[i]->mDistanceFromTarget < currentLowest)
			{
				currentLowest = closedList[i]->mDistanceFromTarget;
				nearest = i;
			}
		}
		currentTile = closedList[nearest];
	}
	while (currentTile->mParent)
	{
		outPath.push(currentTile);
		currentTile = currentTile->mParent;
	}
	outPath.push(currentTile);

	return pathExists;
}

bool Map::lineOfSight(const sf::Vector2f & p1, const sf::Vector2f & p2, float stepSize)
{
	sf::Vector2f current = p1;
	bool done = false;
	while (!done)
	{
		current = VectorFunctions::lerp(current, p2, stepSize, done);
		if (getTileFromIndex(getTileIndexFromCoords(current))->getTextureID() == -1)
			return false;
	}

	return true;
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

	for (auto t : mTiles)
		t.draw(target, states);
}
