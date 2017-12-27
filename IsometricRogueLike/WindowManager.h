#pragma once
#include "Window.h"
#include "DrawThis.h"
#include "EventObserver.h"
#include <vector>
#include <stack>

class WindowManager : public IWindowListener, public EventObserver
{
public:
	WindowManager();
	~WindowManager();

	void addWindow(Window* window);
	void onWindowClose(Window* window);

	bool observe(const sf::Event& _event) override;
	void registerEvents();
	void unregisterEvents();

	void clearGarbage();
	void arrangeWindows(Window* window);

	virtual void drawPrep(DrawingManager* drawingMan);

	static void setup(EventManager* eventManager);

private:

	std::vector<Window*> mWindows;
	std::stack<Window*> mGarbage;
};