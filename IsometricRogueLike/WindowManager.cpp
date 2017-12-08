#include "WindowManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "DrawingManager.h"

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	clearGarbage();
}

void WindowManager::addWindow(Window * window)
{
	window->setWindowListener(this);
	mWindows.insert(window);
}

void WindowManager::onWindowClose(Window * window)
{
	mGarbage.push(window);
	mWindows.erase(window);
}

void WindowManager::registerEvents()
{
	for (auto w : mWindows)
		w->registerEvents();
}

void WindowManager::unregisterEvents()
{
	for (auto w : mWindows)
		w->unregisterEvents();
}

void WindowManager::drawPrep(DrawingManager * drawingMan)
{
	for (auto w : mWindows)
		drawingMan->addDrawable(w);
}

void WindowManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

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
