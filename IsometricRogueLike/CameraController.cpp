#include "CameraController.h"
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "IsometricConversion.h"

CameraController::CameraController() :
	m_center(0.0f, 0.0f), m_zoomLevel(1.0f),
	m_desiredZoomLevel(m_zoomLevel), m_controllable(true)
{
}

CameraController::~CameraController()
{
}

void CameraController::initalize(sf::FloatRect size, sf::RenderWindow* window)
{
	m_renderWindow = window;
	m_center.x = (size.width + size.left) / 2.0f;
	m_center.y = (size.height + size.top) / 2.0f;
	m_cameraView.reset(size);
	updateCamera();
}

void CameraController::moveCamera(const sf::Vector2f &offset)
{
	positionCamera(sf::Vector2f(m_center + offset));
}

void CameraController::positionCamera(const sf::Vector2f & position)
{
	m_center = position;
	sf::Vector2f roundedPos = m_center;
	// IsometricConversion::toIsometric(m_center);

	//printf("X: %f, Y: %f\n", m_center.x, m_center.y);
	// Round off to nearest integer or it will look ugly as fuck
	roundedPos.x = (int)(roundedPos.x);
	roundedPos.y = (int)(roundedPos.y);
	m_cameraView.setCenter(roundedPos);
}

sf::Vector2f CameraController::getCenter() const
{
	return m_center;
}

void CameraController::zoom(bool in)
{

	if (in)
		m_desiredZoomLevel += 0.1f;
	else
		m_desiredZoomLevel -= 0.1f;

	m_desiredZoomLevel = std::max(m_desiredZoomLevel, ZOOM_MIN);
	m_desiredZoomLevel = std::min(m_desiredZoomLevel, ZOOM_MAX);
}

void CameraController::updateCamera()
{
	if (m_renderWindow)
		m_renderWindow->setView(m_cameraView);
}
