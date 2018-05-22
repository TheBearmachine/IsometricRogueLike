#pragma once
#include "Transformabetter.h"
#include "FSM.h"
#include <stack>
#include <vector>

__interface IMovementListener
{
	void onReachTile(const sf::Vector2f &clientPos);
	void onDestinationReached();
};

class Entity;
class Map;
class FSMIdle;
class FSMAction;
struct TileNode;

class Movement : public FSM
{
public:
	Movement(Entity* client, float moveSpeed, FSM** currentStatePtr);
	~Movement();

	void setPath(std::stack<TileNode*> path);
	//void setTarget(Entity* target);
	sf::Vector2f getCurrentTarget() const;
	bool getMoving() const;

	void registerMovementListener(IMovementListener* listener);
	void unregisterMovementListener(IMovementListener* listener);

	void setCurrentMap(Map* currentMap);

	void setMoveSpeed(float moveSpeed);
	void halt();

	void update(const sf::Time& deltaTime) override;
	virtual void exit();
	virtual void entry();

	void setFSMIdle(FSMIdle* fSMIdle);
	void setFSMAction(FSMAction* fSMAction);

	void performAction() override;
	void goIdle() override;

private:
	FSMAction* mFSMAction;
	FSMIdle* mFSMIdle;

	Entity* mClient;
	Map* mCurrentMap;
	std::stack<TileNode*> mPath;
	/*sf::Vector2i mCurrentTargetPos;
	Entity* mCurrentTarget;*/
	std::vector<IMovementListener*> mListeners;

	float mMoveSpeed;
	float mSway;
	bool mHalt;
};