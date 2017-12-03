#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "Transformabetter.h"
#include "EventObserver.h"

__interface IDragListener
{
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos) = 0;
};

namespace sf
{
	class RenderTarget;
}
class EventManager;

class Dragable : public EventObserver, public Transformabetter
{
public:
	Dragable();
	Dragable(IDragListener* listener, const sf::FloatRect &area);
	~Dragable();

	void setListener(IDragListener* listener);
	void setAction(size_t action);

	virtual void registerEvents();
	virtual void unregisterEvents();
	virtual void observe(const sf::Event & _event) override;
	void setup(EventManager* eventManager, sf::RenderTarget* window);

private:
	IDragListener* mListener;
	sf::FloatRect mInteractArea;
	sf::RenderTarget* mWindow;
	EventManager* mEventManager;
	std::vector<sf::Event::EventType> mInterestedEvents;
	bool mDrag;
	sf::Vector2f previousMousePos;
	size_t mAction;
};