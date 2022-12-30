#pragma once

#include "Pipeline.h"

class SolidColorEffect
{
public:
	class Vertex
	{
	public:
		Vertex() = default;
		Vertex( const Vec3& pos )
			:
			pos( pos )
		{}
		// this enables template functions clone a vertex
		// while changing the pos only
		Vertex( const Vec3& pos, const Vertex& src )
			:
			pos( pos )
		{}
		Vertex( const Vec3& pos, const Vec2& t )
			:
			pos( pos )
		{}
		
		Vertex& operator+=( const Vertex& rhs )
		{
			pos += rhs.pos;
			return *this;
		}
		Vertex operator+( const Vertex& rhs ) const
		{
			return Vertex( *this ) += rhs;
		}
		Vertex& operator-=( const Vertex& rhs )
		{
			pos -= rhs.pos;
			return *this;
		}
		Vertex operator-( const Vertex& rhs ) const
		{
			return Vertex( *this ) -= rhs;
		}
		Vertex& operator*=( float rhs )
		{
			pos *= rhs;
			return *this;
		}
		Vertex operator*( float rhs ) const
		{
			return Vertex( *this ) *= rhs;
		}
		Vertex& operator/=( float rhs )
		{
			pos /= rhs;
			return *this;
		}
		Vertex operator/( float rhs ) const
		{
			return Vertex( *this ) /= rhs;
		}
	public:
		Vec3 pos;
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
			return c;
		}
		void BindColor( Color c )
		{
			this->c = c;
		}
	private:
		// prepare clamping constants
		Color c;
	};
public:
	PixelShader ps;

};