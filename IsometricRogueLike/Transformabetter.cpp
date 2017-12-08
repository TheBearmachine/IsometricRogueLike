#include "Transformabetter.h"

Transformabetter::Transformabetter() :
	m_parentTransform(nullptr)
{
}

Transformabetter::Transformabetter(Transformabetter* parentTransform) :
	m_parentTransform(parentTransform)
{
}

Transformabetter::~Transformabetter()
{
}

void Transformabetter::setParentTransform(Transformabetter * parentTransform)
{
	m_parentTransform = parentTransform;
}

sf::Transform Transformabetter::getGlobalTransform() const
{
	sf::Transform trans = getTransform();
	if (m_parentTransform)
		trans = m_parentTransform->getGlobalTransform() * trans;
	return trans;
}
