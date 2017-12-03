#pragma once
#include <string>

namespace Constants
{
	/*namespace Game
	{
		const char* Name = "Isometrica";
		size_t ScreenWidth = 640;
		size_t ScreenHeight = 480;
	}*/

	namespace World
	{
		namespace Tile
		{
			const float Width = 64.0f;
			const float Height = 40.0f;
			const float HalfWidth = Width / 2.0f;
			const float HalfHeight = Height / 2.0f;
		}
	}

	namespace Camera
	{
		const float Speed = 120.0f;
	}

	namespace Filepaths
	{
		const std::string FontsFolder = "Resources/Fonts/";
		const std::string ImagesFolder = "Resources/Images/";
		const std::string DefaultFont = FontsFolder + "NEW_HORIZONS.TTF";
	}
}