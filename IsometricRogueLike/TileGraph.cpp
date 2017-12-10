#include "TileGraph.h"

TileGraph::TileGraph()
{

}

TileGraph::~TileGraph()
{

}

void TileGraph::addTileNode(TileNode tileNode)
{
	mTileGraph.push_back(tileNode);
}

void TileGraph::clearNodes()
{
	mTileGraph.clear();
}

void TileGraph::resetNodeCosts()
{
	for (auto t : mTileGraph)
		t.mAccumulatedCost = -1;
}

TileNode* TileGraph::getNode(const Tile* tile)
{
	for (size_t i = 0; i < mTileGraph.size(); i++)
	{
		if (mTileGraph[i].mTile == tile) return &mTileGraph[i];
	}
	return nullptr;
}

TileNode * TileGraph::getNode(int index)
{
	return &mTileGraph[index];
}
