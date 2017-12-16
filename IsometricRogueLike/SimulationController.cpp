#include "SimulationController.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventManager.h"
#include "Map.h"
#include "Creature.h"
#include "Constants.h"

static sf::RenderTarget* mWindow;
static EventManager* mEventManager;

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
			sf::Vector2f entityPos = mControllableEntity->getMovementComponent()->getCurrentTarget();
			sf::Vector2i targetPos = mCurrentMap->getTileIndexFromCoords(mousePos);
			sf::Vector2i currentPos = mCurrentMap->getTileIndexFromCoords(entityPos);

			mControllableEntity->getMovementComponent()->setPath(mCurrentMap->findPath(currentPos, targetPos));

			//printf("Tile index x: %i, y: %i\n", derp.x, derp.y);
		}
		break;

	case sf::Event::KeyPressed:
		switch (_event.key.code)
		{
		case sf::Keyboard::Space:
			mControllableEntity->getMovementComponent()->halt();
			break;

		default:
			break;
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

void SimulationController::setup(sf::RenderTarget * target, EventManager * eventManager)
{
	mWindow = target;
	mEventManager = eventManager;
}
