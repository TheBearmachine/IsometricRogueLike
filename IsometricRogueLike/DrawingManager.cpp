#include "DrawingManager.h"
//#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

DrawingManager::DrawingManager()
{
}

DrawingManager::~DrawingManager()
{
}

void DrawingManager::addDrawable(DrawThis * drawable)
{
	mDrawables.push_back(drawable);
}

void DrawingManager::draw(sf::RenderTarget * target)
{
	std::map<int, std::vector<DrawThis*>> staticDrawables, dynamicDrawables;
	sf::View prevView = target->getView();
	sf::View GUIView = target->getDefaultView();

	for (auto d : mDrawables)
	{
		if (d->getStaticDrawPosition())
			staticDrawables[d->getZBuffer()].push_back(d);
		else
			dynamicDrawables[d->getZBuffer()].push_back(d);

	}

	for (auto it : dynamicDrawables)
	{
		for (auto itt : it.second)
		{
			target->draw(*itt);
		}
	}
	target->setView(GUIView);
	for (auto it : staticDrawables)
	{
		for (auto itt : it.second)
		{
			target->draw(*itt);
		}
	}
	target->setView(prevView);

	mDrawables.clear();
}
