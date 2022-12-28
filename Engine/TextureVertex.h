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
		return TextureVertex(pos.GetInterpolationTo(other.pos,alpha),tc.GetInterpolationTo(other.tc,alpha));
	}
	TextureVertex&	operator-=( const TextureVertex& rhs )
	{
		pos -= rhs.pos;
		tc -= rhs.tc;
		return *this;
	}
	TextureVertex	operator-( const TextureVertex& rhs ) const
	{
		return TextureVertex(*this) -= rhs;
	}
	TextureVertex&	operator+=( const TextureVertex& rhs )
	{
		pos += rhs.pos;
		tc += rhs.tc;
		return *this;
	}
	TextureVertex	operator+( const TextureVertex& rhs ) const
	{
		return TextureVertex(*this) += rhs;
	}
	TextureVertex&	operator/=( const float rhs )
	{
		pos /= rhs;
		tc /= rhs;
		return *this;
	}
	TextureVertex	operator/( const float rhs ) const
	{
		return TextureVertex(*this) /= rhs;
	}
	TextureVertex&	operator*=( const float rhs )
	{
		pos *= rhs;
		tc *= rhs;
		return *this;
	}
	TextureVertex	operator*( const float rhs ) const
	{
		return TextureVertex(*this) *= rhs;
	}
public:
	Vec3 pos;
	Vec2 tc;
};