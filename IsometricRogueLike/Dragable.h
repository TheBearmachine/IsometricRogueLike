#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Clickable.h"

__interface IDragListener
{
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos) = 0;
};

namespace sf
{
	class RenderTarget;
}
class EventManager;

class Dragable : public Clickable
{
public:
	Dragable();
	Dragable(IDragListener* listener, const sf::Vector2f &size, size_t action);
	~Dragable();

	void setListener(IDragListener* listener);
	void setAction(size_t action);

	virtual void onDragInside(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos) override;

private:
	IDragListener* mListener;
	size_t mAction;
};