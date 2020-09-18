#pragma once
#include "TransformAlgorithm.h"

class TransAlgWalk : public TransformAlgorithm
{
public:
	TransAlgWalk();
	~TransAlgWalk();

	virtual float evaluateRotation(float value) override;
	virtual sf::Vector2f evaluateDisplacement(float value) override;
};
