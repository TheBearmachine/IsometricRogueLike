#include "SimulationController.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventManager.h"
#include "Map.h"

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

bool SimulationController::observe(const sf::Event & _event)
{
	bool retVal = false;
	switch (_event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
			sf::Vector2i derp = mCurrentMap->getTileIndexFromCoords(mousePos);
			mCurrentMap->findPath(sf::Vector2i(2, 2), derp);
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
