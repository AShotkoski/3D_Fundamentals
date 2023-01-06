#pragma once

#include "Pipeline.h"

class GradiantColorEffect
{
public:
	class Vertex
	{
	public:
		Vertex() = default;
		Vertex( const Vec3& pos, const Vec3& col )
			:
			pos( pos ),
			color(col)
		{}
		// this enables template functions clone a vertex
		// while changing the pos only
		Vertex( const Vec3& pos, const Vertex& src )
			:
			color( src.color ),
			pos( pos )
		{}
		Vertex& operator+=( const Vertex& rhs )
		{
			pos += rhs.pos;
			color += rhs.color;
			return *this;
		}
		Vertex operator+( const Vertex& rhs ) const
		{
			return Vertex( *this ) += rhs;
		}
		Vertex& operator-=( const Vertex& rhs )
		{
			pos -= rhs.pos;
			color -= rhs.color;
			return *this;
		}
		Vertex operator-( const Vertex& rhs ) const
		{
			return Vertex( *this ) -= rhs;
		}
		Vertex& operator*=( float rhs )
		{
			pos *= rhs;
			color *= rhs;
			return *this;
		}
		Vertex operator*( float rhs ) const
		{
			return Vertex( *this ) *= rhs;
		}
		Vertex& operator/=( float rhs )
		{
			pos /= rhs;
			color /= rhs;
			return *this;
		}
		Vertex operator/( float rhs ) const
		{
			return Vertex( *this ) /= rhs;
		}
	public:
		Vec3 pos;
		Vec3 color;
	};


	// invoked for each pixel of a triangle
	// takes an input of attributes that are the
	// result of interpolating vertex attributes
	// and outputs a color
	class PixelShader
	{
	public:
		template <typename Input>
		Color operator()( Input& in )
		{
			
			return Color(in.color);
		}
	private:
		
	};
public:
	PixelShader ps;

};