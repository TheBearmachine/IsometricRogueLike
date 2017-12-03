#pragma once
#include "Button.h"
#include <SFML/Graphics/Drawable.hpp>

class TestButtonContainer: public Transformabetter, public IButtonListener, public sf::Drawable
{
public:
	TestButtonContainer();
	~TestButtonContainer();

	void setup(EventManager* eventManager, sf::RenderTarget* window);
	void setButtonPosition(const sf::Vector2f &pos);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	virtual void buttonAction(unsigned int action) override;

	Button button;
};