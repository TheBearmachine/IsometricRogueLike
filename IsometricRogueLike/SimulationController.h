#pragma once
#include "EventObserver.h"
#include "Movement.h"
#include "Window.h"
#include "Inventoryslot.h"
#include "Button.h"
#include <SFML/Window/Event.hpp>
#include <vector>

class Map;
class Creature;
class EventManager;
class MousePointer;
class ContentRegionInventory;
class ContentRegionMenu;
namespace sf
{
	class RenderTarget;
}

class SimulationController : public EventObserver, public IMovementListener, public IWindowListener, public IInventoryslotListener, public IButtonListener
{
public:
	SimulationController();
	~SimulationController();

	void initalize(Map* map, Creature* controllableEntity);

	virtual bool observe(const sf::Event& _event) override;
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;

	void onReachTile(const sf::Vector2f &clientPos) override;
	void onDestinationReached() override;

	void onWindowClose(Window* window) override;

	void buttonAction(Item* item, Inventoryslot* invSlot);

	void buttonAction(unsigned int action);


	static void setup(sf::RenderTarget* target, EventManager* eventManager, MousePointer* mouseP);

private:
	enum MenuButtons
	{
		Move,
		Attack,
		Interact,
	};

	std::vector<sf::Event::EventType> mInterestedEvents;
	Map* mCurrentMap;
	Creature* mControllableEntity;
	Window* mInventoryWin;
	Window* mCharacterWin;
	Window* mRightClickWindow;
	ContentRegionInventory* mRightClickCRI;
	ContentRegionMenu* mRightClickCRM;
	sf::Vector2i mRightClickTile;
};