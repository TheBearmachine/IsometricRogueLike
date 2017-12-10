#include "SimulationController.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventManager.h"
#include "Map.h"
#include "Entity.h"

static sf::RenderTarget* mWindow;
static EventManager* mEventManager;

SimulationController::SimulationController()
{
	setStaticEventPosition(false);
	mInterestedEvents.push_back(sf::Event::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::KeyPressed);
}

SimulationController::~SimulationController()
{

}

void SimulationController::setCurrentMap(Map * map)
{
	mCurrentMap = map;
}

void SimulationController::setControllableEntity(Entity * controllableEntity)
{
	mControllableEntity = controllableEntity;
}

bool SimulationController::observe(const sf::Event & _event)
{
	bool retVal = false;
	switch (_event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			if (!mControllableEntity || !mCurrentMap) break;
			retVal = true;
			sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
			sf::Vector2f entityPos = mControllableEntity->getCurrentMoveTarget();
			sf::Vector2i targetPos = mCurrentMap->getTileIndexFromCoords(mousePos);
			sf::Vector2i currentPos = mCurrentMap->getTileIndexFromCoords(entityPos);

			mControllableEntity->setPath(mCurrentMap->findPath(currentPos, targetPos));

			//printf("Tile index x: %i, y: %i\n", derp.x, derp.y);
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

void SimulationController::setup(sf::RenderTarget * target, EventManager * eventManager)
{
	mWindow = target;
	mEventManager = eventManager;
}
