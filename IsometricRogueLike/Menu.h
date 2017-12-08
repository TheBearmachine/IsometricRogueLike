#pragma once
#include <vector>
#include "Transformabetter.h"
#include "DrawThis.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Button;

class Menu : public DrawThis, public Transformabetter
{
public:
	Menu(const sf::Vector2f &size);
	~Menu();

	void addButton(Button* button);
	void clearButtons();

	void setBackgroundSize(const sf::Vector2f &size);
	sf::Vector2f getBackgroundSize() const;

	void registerEvents();
	void unregisterEvents();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::vector<Button*> mButtons;

	sf::RectangleShape mBackground;
};