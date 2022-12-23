#pragma once
#include "Vec3.h"
#include "Graphics.h"

class PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor( (float)Graphics::ScreenWidth / 2.f ),
		yFactor( (float)Graphics::ScreenHeight / 2.f)
	{}
	void Transform( Vec3& v )
	{
		v.x = (1.f + v.x) * xFactor;
		v.y = (1.f - v.y) * yFactor;
	}
private:
	float xFactor;
	float yFactor;
};