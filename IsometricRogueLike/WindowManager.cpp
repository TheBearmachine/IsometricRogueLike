#include "WindowManager.h"
#include "EventManager.h"
#include "DrawingManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const int ZB = 1000;

static EventManager* mEventManager;

WindowManager::WindowManager()
{
	mInterestedEvents.push_back(sf::Event::EventType::MouseMoved);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
    mInterestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);
    mInterestedEvents.push_back(sf::Event::EventType::MouseWheelScrolled);
}

WindowManager::~WindowManager()
{
	clearGarbage();
}

void WindowManager::addWindow(Window * window)
{
	window->setWindowListener(this);
	window->setZBuffer(ZB - (int)mWindows.size());
	mWindows.push_back(window);
}

void WindowManager::onWindowClose(Window * window)
{
	int count = 0;
	mGarbage.push(window);
	std::vector<Window*> temp;
	for (size_t i = 0; i < mWindows.size(); i++)
	{
		if (mWindows[i] != window)
		{
			temp.push_back(mWindows[i]);
			mWindows[i]->setZBuffer(ZB - count);
			count++;
		}
	}
	mWindows = temp;
}

bool WindowManager::observe(const sf::Event & _event)
{
	bool retVal = false;
	for (auto w : mWindows)
		if (!retVal)
		{
			if (w->getVisible())
				retVal = w->observe(_event);
		}
		else
			w->resetState();

	return retVal;
}

void WindowManager::registerEvents()
{
	mEventManager->registerObserver(this, mInterestedEvents);
}

void WindowManager::unregisterEvents()
{
	mEventManager->unregisterObserver(this, mInterestedEvents);
}

void WindowManager::drawPrep(DrawingManager * drawingMan)
{
	for (auto w : mWindows)
		drawingMan->addDrawable(w);
}

void WindowManager::setup(EventManager * eventManager)
{
	mEventManager = eventManager;
}

void WindowManager::clearGarbage()
{
	while (!mGarbage.empty())
	{
		mGarbage.top()->unregisterEvents();
		delete mGarbage.top();
		mGarbage.pop();
	}
}

void WindowManager::arrangeWindows(Window * window)
{
	for (size_t i = 0; i < mWindows.size(); i++)
	{
		if (mWindows[i] == window)
		{
			if (i == 0) return;

			while (i > 0)
			{

				// Swap the indices
				Window* temp = mWindows[i - 1];
				mWindows[i - 1] = mWindows[i];
				mWindows[i] = temp;

				mWindows[i - 1]->setZBuffer(ZB - (int)i);
				mWindows[i]->setZBuffer(ZB - (int)i - 1);

				i--;
			}

			return;
		}
	}
}
