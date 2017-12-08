#pragma once
#include "DrawThis.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class DrawingManager
{
public:
	DrawingManager();
	~DrawingManager();

	void addDrawable(DrawThis* drawable);

	void draw(sf::RenderTarget* target);

private:
	std::vector<DrawThis*> mDrawables;
};