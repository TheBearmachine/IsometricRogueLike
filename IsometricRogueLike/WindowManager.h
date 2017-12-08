#pragma once
#include "Window.h"
#include <set>
#include <stack>
#include "DrawThis.h"

class WindowManager : public IWindowListener, public DrawThis
{
public:
	WindowManager();
	~WindowManager();

	void addWindow(Window* window);
	void onWindowClose(Window* window);

	void registerEvents();
	void unregisterEvents();

	void clearGarbage();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:

	std::set<Window*> mWindows;
	std::stack<Window*> mGarbage;
};