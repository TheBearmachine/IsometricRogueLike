#include "Movement.h"
#include "Constants.h"
#include "VectorFunctions.h"
#include "TileGraph.h"
#include "Tile.h"
#include <SFML/System/Time.hpp>

Movement::Movement(Transformabetter * client, float moveSpeed) :
	mClient(client), mMoveSpeed(moveSpeed)
{

}

Movement::~Movement()
{

}

void Movement::setPath(std::stack<TileNode*> path)
{
	mPath = path;
}

sf::Vector2f Movement::getCurrentTarget() const
{
	sf::Vector2f retVec = mClient->getPosition();

	if (!mPath.empty())
	{
		retVec = mPath.top()->mTile->getWorldPos();
		retVec.x += Constants::World::Tile::HalfWidth;
	}

	return retVec;
}

void Movement::setMoveSpeed(float moveSpeed)
{
	mMoveSpeed = moveSpeed;
}

void Movement::update(const sf::Time & deltaTime)
{
	if (!mPath.empty())
	{
		float speed = deltaTime.asSeconds() * mMoveSpeed;
		bool goalReached = false;

		sf::Vector2f curPos = mClient->getPosition(), targetPos = mPath.top()->mTile->getWorldPos();
		targetPos.x += Constants::World::Tile::HalfWidth;
		sf::Vector2f newPos = VectorFunctions::lerp(curPos, targetPos, speed, goalReached);
		mClient->setPosition(newPos);

		if (goalReached)
			mPath.pop();
	}


}
