#pragma once
#include <limits>
#include <vector>
#include "Graphics.h"


class ZBuffer
{
public:
	ZBuffer()
	{
		pixelDepths.resize( Graphics::ScreenWidth * Graphics::ScreenHeight, 
			std::numeric_limits<float>::infinity() );
	}
private:
	std::vector<float> pixelDepths;
};