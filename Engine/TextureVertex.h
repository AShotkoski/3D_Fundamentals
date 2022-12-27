#pragma once
#include "Vec3.h"

class TextureVertex
{
public:
	TextureVertex() = default;
	TextureVertex( const Vec3& pos_in, const Vec2& tc_in )
		:
		pos( pos_in ),
		tc( tc_in )
	{}
	TextureVertex GetInterpolationTo( const TextureVertex& other, const float alpha ) const
	{
		TextureVertex ret(pos.GetInterpolationTo(other.pos,alpha),tc.GetInterpolationTo(other.tc,alpha));
	}
public:
	Vec3 pos;
	Vec2 tc;
};