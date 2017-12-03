#include "TestButtonContainer.h"
#include <SFML/Graphics/RenderTarget.hpp>

TestButtonContainer::TestButtonContainer():
	button()
{
	button.setListener(this);
	button.setParentTransform(this);
}

TestButtonContainer::~TestButtonContainer()
{
}

void TestButtonContainer::setup(EventManager * eventManager, sf::RenderTarget * window)
{
	button.setup(eventManager, window);
	button.registerEvents();
}

void TestButtonContainer::setButtonPosition(const sf::Vector2f & pos)
{
	button.setPosition(pos);
}

void TestButtonContainer::buttonAction(unsigned int action)
{
	printf("Click!");
}

void TestButtonContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(button, states);
}
