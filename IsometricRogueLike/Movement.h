#pragma once
#include "Transformabetter.h"
#include <stack>

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
	void setMoveSpeed(float moveSpeed);

	virtual void update(const sf::Time& deltaTime);

private:
	Transformabetter* mClient;
	std::stack<TileNode*> mPath;

	float mMoveSpeed;
};