#pragma once
#include "Transformabetter.h"
#include <map>

class Entity;
class Map;
namespace sf
{
	class Time;
}

class Action
{
public:
	typedef std::map<std::string, size_t> WorldState;

	enum ActionTypes
	{
		PickUpItem,
		AttackTarget
	};

	enum Goals
	{

	};

	Action();
	~Action();

	virtual bool isDone() = 0;
	virtual bool inRange() = 0;
	virtual bool checkProceduralPrecondition(Entity* agent) = 0;
	virtual bool update(const sf::Time& deltaTime) = 0;
	void setCost(float newCost);
	float getCost() const;
	void addPrecondition(const std::string &key, size_t val);
	void removePrecondition(const std::string &key);
	const WorldState& getPreconditions() const;
	void addEffect(const std::string &key, size_t val);
	void removeEffect(const std::string &key);
	const WorldState& getEffects() const;

	static void setCurrentMap(Map* currentMap);

protected:
	static Map* getCurrentMap();

private:
	WorldState mPreconditions;
	WorldState mEffects;
	float mCost;
};
