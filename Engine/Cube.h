#pragma once
#include "Vec3.h"
#include <vector>
#include "IndexedLineList.h"
#include "IndexedTriangleList.h"
#include "TextureVertex.h"

class Cube
{
public:
	Cube( float size )
	{
		float pt = size / 2.f;
		verts.emplace_back(-pt,  pt, -pt); //0
		tcs.emplace_back( 0.f, 1.f );
		verts.emplace_back( pt,  pt, -pt); //1
		tcs.emplace_back( 1.f, 1.f );
		verts.emplace_back( pt,  pt,  pt); //2
		tcs.emplace_back( 0.f, 1.f );
		verts.emplace_back(-pt,  pt,  pt); //3
		tcs.emplace_back( 1.f, 1.f );
		verts.emplace_back(-pt, -pt,  pt); //4
		tcs.emplace_back( 1.f, 0.f );
		verts.emplace_back( pt, -pt,  pt); //5
		tcs.emplace_back( 0.f, 0.f );
		verts.emplace_back( pt, -pt, -pt); //6
		tcs.emplace_back( 0.f, 0.f );
		verts.emplace_back(-pt, -pt, -pt); //7
		tcs.emplace_back( 1.f, 0.f );
	}

	IndexedLineList GetLines() const
	{
		return
		{
			verts,{
				0,1,  0,3,  1,2,  2,3,
				0,7,  1,6,  2,5,  3,4,
				7,6,  6,5,  5,4,  4,7
				}
		};
	}
	IndexedTriangleList<Vec3> GetTriangles() const
	{
		return
		{
			verts,{
				0,6,7,  0,1,6,
				3,1,0,  3,2,1,
				1,5,6,  1,2,5,
				2,4,5,  2,3,4,
				3,7,4,  3,0,7,
				7,5,4,  7,6,5
				}
		};
	}
	IndexedTriangleList<TextureVertex> GetTexTriangles() const
	{
		std::vector<TextureVertex> ret;
		ret.reserve( verts.size() );
		for ( size_t i = 0; i < verts.size(); i++ )
		{
			ret.emplace_back( verts[i], tcs[i] );
		}

		return
		{
			std::move(ret),{
				0,6,7,  0,1,6,
				3,1,0,  3,2,1,
				1,5,6,  1,2,5,
				2,4,5,  2,3,4,
				3,7,4,  3,0,7,
				7,5,4,  7,6,5
				}
		};
	}

public:
	std::vector<Vec2> tcs;
	std::vector<Vec3> verts;
};