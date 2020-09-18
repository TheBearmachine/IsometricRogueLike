#pragma once
#include "TransformAlgorithm.h"

class TransAlgMad : public TransformAlgorithm
{
public:
	TransAlgMad();
	~TransAlgMad();

	virtual float evaluateRotation(float value) override;
	virtual sf::Vector2f evaluateDisplacement(float value) override;
};
