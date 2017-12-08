#pragma once
#include <string>
#include <SFML/Graphics/Color.hpp>

namespace Constants
{
	namespace Game
	{
		static const char* Name = "Isometrica";
		static const size_t ScreenWidth = 640;
		static const size_t ScreenHeight = 480;

		static const sf::Color WindowBorderColor(0, 0, 220);
		static const sf::Color WindowFillColor(0, 0, 170);
		static const sf::Color WindowTopBorderColor(0, 40, 200);
		static const sf::Color WindowTopFillColor(0, 20, 170);
	}

	namespace World
	{
		namespace Tile
		{
			static const float Width = 64.0f;
			static const float Height = 40.0f;
			static const float HalfWidth = Width / 2.0f;
			static const float HalfHeight = Height / 2.0f;
		}
		namespace Wall
		{
			static const float Width = 32.0f;
			static const float Height = 60.0f;
		}
	}

	namespace Camera
	{
		static const float Speed = 120.0f;
	}

	namespace Filepaths
	{
		static const std::string FontsFolder = "Resources/Fonts/";
		static const std::string ImagesFolder = "Resources/Images/";
		static const std::string DefaultFont = FontsFolder + "NEW_HORIZONS.TTF";
	}
}