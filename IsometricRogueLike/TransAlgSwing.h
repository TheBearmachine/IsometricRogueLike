#pragma once
#include "TransformAlgorithm.h"

class TransAlgSwing : public TransformAlgorithm
{
public:
	TransAlgSwing();
	~TransAlgSwing();

	virtual float evaluateRotation(float value) override;
	virtual sf::Vector2f evaluateDisplacement(float value) override;

private:

};
