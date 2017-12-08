#pragma once
#include <SFML/Graphics/Transformable.hpp>

class Transformabetter : public sf::Transformable
{
public:
	Transformabetter();
	Transformabetter(Transformabetter* parentTransform);
	~Transformabetter();

	void setParentTransform(Transformabetter* parentTransform);
	sf::Transform getGlobalTransform() const;

private:
	Transformabetter* m_parentTransform;
};