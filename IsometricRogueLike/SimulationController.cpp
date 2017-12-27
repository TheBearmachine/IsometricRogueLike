#include "SimulationController.h"
#include "EventManager.h"
#include "Map.h"
#include "Window.h"
#include "ContentRegionInventory.h"
#include "ContentRegionCharacterAttributes.h"
#include "Creature.h"
#include "Constants.h"
#include "MousePointer.h"
#include <SFML/Graphics/RenderTarget.hpp>

static sf::RenderTarget* mWindow;
static EventManager* mEventManager;
static MousePointer* mMousePointer;

static const int TempDist = 170;
static const int TempTime = 10;

SimulationController::SimulationController()
{
	setStaticEventPosition(false);
	mInterestedEvents.push_back(sf::Event::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::KeyPressed);
}

SimulationController::~SimulationController()
{

}

void SimulationController::initalize(Map * map, Creature * controllableEntity)
{
	mCurrentMap = map;
	mControllableEntity = controllableEntity;
	mCurrentMap->updateVertexArray(mControllableEntity->getPosition(), TempDist, TempTime);
	mControllableEntity->getMovementComponent()->registerMovementListener(this);
	mControllableEntity->getMovementComponent()->setCurrentMap(mCurrentMap);
	Inventory* inv = mControllableEntity->getInventory();

	bool success = true;

	success = Window::createWindow(&mInventoryWin, "Inventory", sf::Vector2f(100.0f, 50.0f), sf::Vector2f());
	ContentRegionInventory* cr = new ContentRegionInventory(inv, 5);
	mInventoryWin->setWindowContentSize(cr->getRegionSize());
	mInventoryWin->addContentRegion(cr);
	mInventoryWin->setVisibility(false);
	mInventoryWin->setWindowListener(this);

	success = Window::createWindow(&mCharacterWin, "Character", sf::Vector2f(100.0f, 50.0f));
	ContentRegionCharacterAttributes* cr2 = new ContentRegionCharacterAttributes();
	mCharacterWin->setWindowContentSize(cr2->getRegionSize());
	mCharacterWin->addContentRegion(cr2);
	mCharacterWin->setVisibility(false);
	mCharacterWin->setWindowListener(this);

}

bool SimulationController::observe(const sf::Event & _event)
{
	bool retVal = false;
	switch (_event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			if (!mControllableEntity || !mCurrentMap || !mMousePointer) break;
			retVal = true;
			sf::Vector2f entityPos = mControllableEntity->getMovementComponent()->getCurrentTarget();
			sf::Vector2i currentPos = mCurrentMap->getTileIndexFromCoords(entityPos);
			if (mMousePointer->getItem() == nullptr)
			{
				sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
				sf::Vector2i targetPos = mCurrentMap->getTileIndexFromCoords(mousePos);

				mControllableEntity->getMovementComponent()->setPath(mCurrentMap->findPath(currentPos, targetPos));
			}
			else
			{
				mCurrentMap->getTileFromIndex(currentPos)->addItem(mMousePointer->switchItem(nullptr));
			}
		}
		break;

	case sf::Event::KeyPressed:
		if (_event.key.code == sf::Keyboard::Space)
		{
			mControllableEntity->getMovementComponent()->halt();
		}
		else if (_event.key.code == sf::Keyboard::I)
		{
			bool vis = !mInventoryWin->getVisible();
			mInventoryWin->setVisibility(vis);
		}
		else if (_event.key.code == sf::Keyboard::C)
		{
			bool vis = !mCharacterWin->getVisible();
			mCharacterWin->setVisibility(vis);
		}

		break;

	default:
		break;
	}

	return retVal;
}

void SimulationController::registerEvents()
{
	mEventManager->registerObserver(this, mInterestedEvents);
}

void SimulationController::unregisterEvents()
{
	mEventManager->unregisterObserver(this, mInterestedEvents);
}

void SimulationController::onReachTile(const sf::Vector2f & clientPos)
{
	mCurrentMap->updateVertexArray(clientPos, TempDist, TempTime);
}

void SimulationController::onWindowClose(Window * window)
{
	window->setVisibility(false);
}

void SimulationController::setup(sf::RenderTarget * target, EventManager * eventManager, MousePointer* mouseP)
{
	mWindow = target;
	mEventManager = eventManager;
	mMousePointer = mouseP;
}
