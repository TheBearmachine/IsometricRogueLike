#pragma once
#include "DrawThis.h"
#include "Transformabetter.h"
#include "IEntityManager.h"
#include "Action.h"
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Map;
class Action;
class FSM;
class FSMAction;
class FSMIdle;
class Movement;
class CharacterAttributes;
class Inventory;
namespace sf
{
	class Time;
}

class Entity : public DrawThis, public Transformabetter
{
public:
	//Entity(const std::string &textureName);
	Entity(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
	~Entity();

	virtual void update(const sf::Time &deltaTime);

	void setDoesTick(bool tick);
	bool getDoesTick() const;

	void moveToTile(const sf::Vector2i & startTile, Map* currentMap);

	virtual Movement* getMovementComponent();
	virtual FSMAction* getFSMActionComponent();
	virtual FSMIdle* getFSMIdleComponent();
	virtual FSM* getCurrentFSMState();

	virtual CharacterAttributes* getCharacterAttributes();
	virtual Inventory* getInventory();

	void remove();
	bool getGarbage() const;

	void setAlive(bool isAlive);
	bool getAlive() const;

	void setFadeMax(float val);
	void reduceFadeCurrent(float deltaVal);
	float getFadeRatio() const;

	void addAvailableAction(Action::ActionTypes actionType);
	const std::vector<Action::ActionTypes>& getAvailableActions() const;

	void setWorldState(const std::string &key, size_t val);
	const Action::WorldState& getWorldState() const;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	static void setup(IEntityManager* entityManager);
	IEntityManager* getEntityManager();

protected:
	sf::Sprite mSprite;

private:
	std::vector<Action::ActionTypes> mAvailableActions;
	Action::WorldState mWorldState;
	bool mGarbage;
	bool mAlive;
	bool mTick;
	float mFadeMax, mFadeCurrent;
};