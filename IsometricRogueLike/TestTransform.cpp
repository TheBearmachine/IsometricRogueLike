#include "TestTransform.h"

TestTransform::TestTransform()
{

}

TestTransform::~TestTransform()
{

}

void TestTransform::derp()
{
	sf::Vector2f globPos = getGlobalTransform().transformPoint(0.0f, 0.0f);
	sf::Vector2f locPos = getPosition();
	printf("Global X: %f, Y: %f - ", globPos.x, globPos.y);
	printf("Local X: %f, Y: %f\n\n", locPos.x, locPos.y);
}
