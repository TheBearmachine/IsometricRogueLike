#pragma once
#include "EventObserver.h"
#include "Transformabetter.h"
#include <SFML/Window/Event.hpp>
#include <vector>

namespace sf
{
	class RenderTarget;
}
class EventManager;

class Clickable : public EventObserver, public Transformabetter
{
public:
	Clickable();
	Clickable(const sf::Vector2f &size);
	virtual ~Clickable();

	void setSize(const sf::Vector2f &size);

	virtual bool observe(const sf::Event & _event);
	virtual void onMouseOver(bool mouseOver);
	virtual void onClickInside();
	virtual void onReleaseInside();
	virtual void onDragInside(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos);

	void resetState();

protected:
	sf::Vector2f mSize;
	bool mMouseInside;
	bool mDrag;
	sf::Vector2f mPreviousMousePos;

public:
	static void setup(sf::RenderTarget* window);
};
