#pragma once
#include <vector>
#include <unordered_set>
#include <SFML/System/Vector2.hpp>

class Tile;

struct TileNode
{
public:
	TileNode()
	{
		for (int i = 0; i < 4; i++) mNeighbors[i] = nullptr;
		mParent = nullptr;
		mTile = nullptr;
	}
	~TileNode() {}

	enum Neightbor
	{
		Right,
		Down,
		Left,
		Up
	};
	// 0 right, 1 down, 2 left, 3 up
	TileNode* mNeighbors[4];
	TileNode* mParent;
	const Tile* mTile;

	int mAccumulatedCost;
};

struct CompareTileNodeCosts
{
	bool operator()(const TileNode *t1, const TileNode *t2)
	{
		return t1->mAccumulatedCost > t2->mAccumulatedCost;
	}
};

class TileGraph
{
public:
	TileGraph();
	~TileGraph();

	void addTileNode(TileNode tileNode);
	void clearNodes();
	void resetNodeCosts();
	TileNode* getNode(const Tile* tile);
	TileNode* getNode(int index);

private:
	std::vector<TileNode> mTileGraph;
};
