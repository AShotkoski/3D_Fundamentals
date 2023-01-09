/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Colors.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "Vec3.h"

class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( const Color& col )
		:
		dword( col.dword )
	{}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}
	explicit Color( const Vec3& c )
		:
		Color((unsigned char)c.x, (unsigned char)c.y, (unsigned char)c.z)
	{	}
	explicit operator Vec3() const
	{
		return { (float)GetR(), (float)GetG(), (float)GetB() };
	}
	Color& operator =( Color color )
	{
		dword = color.dword;
		return *this;
	}
	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeRGB( 255u,255u,255u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	static constexpr Color Red = MakeRGB( 255u,0u,0u );
	static constexpr Color Green = MakeRGB( 0u,255u,0u );
	static constexpr Color Blue = MakeRGB( 0u,0u,255u );
	static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	static constexpr Color Cyan = MakeRGB( 0u,255u,255u );
	static constexpr Color Magenta = MakeRGB( 255u,0u,255u );
	static constexpr Color HotPink = MakeRGB( 255u,105u,180u );
	static constexpr Color DeepPink = MakeRGB( 255u,20u,147u );
	static constexpr Color Coral = MakeRGB( 255u,127u,80u );
	static constexpr Color Tomato = MakeRGB( 255u,99u,71u );
	static constexpr Color OrangeRed = MakeRGB( 255u,69u,0u );
	static constexpr Color DarkOrange = MakeRGB( 255u,140u,0u );
	static constexpr Color Orange = MakeRGB( 255u,165u,0u );
	static constexpr Color Gold = MakeRGB( 255u,215u,0u );
	static constexpr Color PeachPuff = MakeRGB( 255u,218u,185u );
	static constexpr Color Khaki = MakeRGB( 240u,230u,140u );
	static constexpr Color DarkKhaki = MakeRGB( 189u,183u,107u );
	static constexpr Color DarkViolet = MakeRGB( 148u,0u,211u );
	static constexpr Color DarkGreen = MakeRGB( 0u,100u,0u );
	static constexpr Color MediumAquamarine = MakeRGB( 102u,205u,170u );
	static constexpr Color Teal = MakeRGB( 0u,128u,128u );
	static constexpr Color Maroon = MakeRGB( 128u,0u,0u );
	static constexpr Color GhostWhite = MakeRGB( 248u,248u,255u );
}