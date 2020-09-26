#include "EventManager.h"
#include "EventObserver.h"
#include <SFML/Graphics/RenderTarget.hpp>

EventManager::EventManager() :
	mObservers()
{

}

EventManager::~EventManager()
{

}

void EventManager::registerObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types)
{
	for (auto t : types)
		registerObserver(observer, t);
}

void EventManager::registerObserver(EventObserver* observer, const sf::Event::EventType& type)
{
	mObservers[type].push_back(observer);
}

void EventManager::unregisterObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types)
{
	for (auto t : types)
		unregisterObserver(observer, t);
}

void EventManager::unregisterObserver(EventObserver* observer, const sf::Event::EventType& type)
{
	size_t size = mObservers[type].size();
	ObserverVec newVec;
	for (size_t i = 0; i < size; i++)
	{
		EventObserver* compare = mObservers[type][i];
		if (compare != observer) newVec.push_back(mObservers[type][i]);
	}
	mObservers[type] = newVec;
}

void EventManager::notify(const sf::Event & _event, sf::RenderTarget* target) const
{

	if (mObservers.find(_event.type) != mObservers.end())
	{
		bool onlyOneReceiver = false;
		const ObserverVec observers = mObservers.at(_event.type);
		sf::View prevView = target->getView();
		sf::View GUIView = target->getDefaultView();

		target->setView(GUIView);
		for (auto rit = observers.rbegin(); rit != observers.rend(); ++rit)
		{
			if ((*rit)->getStaticEventPosition())
			{
				onlyOneReceiver = (*rit)->observe(_event);
				if (onlyOneReceiver && (
					_event.type == sf::Event::MouseButtonPressed ||
					_event.type == sf::Event::MouseButtonReleased ||
					_event.type == sf::Event::MouseMoved ||
					_event.type == sf::Event::MouseWheelScrolled
					))
				{
					target->setView(prevView);
					return;
				}
			}
		}

		target->setView(prevView);
		for (auto rit = observers.rbegin(); rit != observers.rend(); ++rit)
		{
			if (!(*rit)->getStaticEventPosition())
			{
				onlyOneReceiver = (*rit)->observe(_event);
				if (onlyOneReceiver && (
					_event.type == sf::Event::MouseButtonPressed ||
					_event.type == sf::Event::MouseButtonReleased))
				{
					return;
				}
			}
		}
	}
}
