#pragma once
#include "Transformabetter.h"
#include <stack>
#include <vector>

__interface IMovementListener
{
	void onReachTile(const sf::Vector2f &clientPos);
};

struct TileNode;
namespace sf
{
	class Time;
}

class Movement
{
public:
	Movement(Transformabetter* client, float moveSpeed);
	~Movement();

	void setPath(std::stack<TileNode*> path);
	sf::Vector2f getCurrentTarget() const;

	void registerMovementListener(IMovementListener* listener);
	void unregisterMovementListener(IMovementListener* listener);

	void setMoveSpeed(float moveSpeed);
	void halt();

	virtual void update(const sf::Time& deltaTime);

private:
	Transformabetter* mClient;
	std::stack<TileNode*> mPath;
	std::vector<IMovementListener*> mListeners;

	float mMoveSpeed;
	bool mHalt;
};