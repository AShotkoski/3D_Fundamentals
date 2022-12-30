#pragma once

#include "Pipeline.h"

class TextureEffect
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
			t( src.t ),
			pos( pos )
		{}
		Vertex( const Vec3& pos, const Vec2& t )
			:
			t( t ),
			pos( pos )
		{}
		Vertex& operator+=( const Vertex& rhs )
		{
			pos += rhs.pos;
			t += rhs.t;
			return *this;
		}
		Vertex operator+( const Vertex& rhs ) const
		{
			return Vertex( *this ) += rhs;
		}
		Vertex& operator-=( const Vertex& rhs )
		{
			pos -= rhs.pos;
			t -= rhs.t;
			return *this;
		}
		Vertex operator-( const Vertex& rhs ) const
		{
			return Vertex( *this ) -= rhs;
		}
		Vertex& operator*=( float rhs )
		{
			pos *= rhs;
			t *= rhs;
			return *this;
		}
		Vertex operator*( float rhs ) const
		{
			return Vertex( *this ) *= rhs;
		}
		Vertex& operator/=( float rhs )
		{
			pos /= rhs;
			t /= rhs;
			return *this;
		}
		Vertex operator/( float rhs ) const
		{
			return Vertex( *this ) /= rhs;
		}
	public:
		Vec3 pos;
		Vec2 t;
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
			assert( isTexBound );
			return pTex->GetPixel(
				(unsigned int)std::min( in.t.x * tex_width + 0.5f, tex_xclamp ),
				(unsigned int)std::min( in.t.y * tex_height + 0.5f, tex_yclamp ));
		}
		void BindTexture(const std::wstring filename)
		{
			pTex = std::make_unique<Surface>( Surface::FromFile( filename ) );

			tex_width = float( pTex->GetWidth() );
			tex_height = float( pTex->GetHeight() );
			tex_xclamp = tex_width - 1.0f;
			tex_yclamp = tex_height - 1.0f;
			isTexBound = true;
		}
	private:
		// prepare clamping constants
		std::unique_ptr<Surface> pTex;

		float tex_width;
		float tex_height;
		float tex_xclamp;
		float tex_yclamp;
		bool isTexBound = false;
	};
public:
	PixelShader ps;
	
};