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
	template <class Vertex>
	Vertex& Transform( Vertex& v ) const
	{
		const float zInv = 1.f / v.pos.z;

		//divide everthing (think tc) by z inv, this lets us interpolate over the inverse version and 
		//get textures that aren't fucked
		v *= zInv;

		v.pos.x = (1.f + v.pos.x ) * xFactor;
		v.pos.y = (1.f  - v.pos.y ) * yFactor;

		//store the inverse of z in v pos z;
		v.pos.z = zInv;

		return v;
	}

	template <class Vertex>
	Vertex GetTransformed( const Vertex& v ) const
	{	
		return Transform( Vertex(v) );
	}
private:
	float xFactor;
	float yFactor;
};