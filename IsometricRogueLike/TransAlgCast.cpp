#include "TransAlgCast.h"
#include "Constants.h"
#include <cmath>

TransAlgCast::TransAlgCast()
{}

TransAlgCast::~TransAlgCast()
{}

float TransAlgCast::evaluateRotation(float value)
{
	if (value >= 0.25f &&
		value <= 0.75f)
		return  sinf((value - 0.25f) * Constants::PI * 2.0f);
	else
		return 0.0f;
}

sf::Vector2f TransAlgCast::evaluateDisplacement(float value)
{
	float v = -std::powf((value - 0.5f) * 4.0f, 2) + 1;
	return sf::Vector2f(0.0f, v);
}
