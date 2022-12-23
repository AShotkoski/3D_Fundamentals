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
	Vec3& Transform( Vec3& v ) const
	{
		v.x = (1.f + v.x) * xFactor;
		v.y = (1.f - v.y) * yFactor;
		return v;
	}
	Vec3 GetTransformed( const Vec3& v ) const
	{	
		return Transform( Vec3(v) );
	}
private:
	float xFactor;
	float yFactor;
};