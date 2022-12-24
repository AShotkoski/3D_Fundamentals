#pragma once
#include "Vec3.h"
#include <vector>
#include "IndexedLineList.h"
#include "IndexedTriangleList.h"

class Cube
{
public:
	Cube( float size )
	{
		float pt = size / 2.f;
		verts.emplace_back(-pt,  pt, -pt);
		verts.emplace_back( pt,  pt, -pt);
		verts.emplace_back( pt,  pt,  pt);
		verts.emplace_back(-pt,  pt,  pt);
		verts.emplace_back(-pt, -pt,  pt);
		verts.emplace_back( pt, -pt,  pt);
		verts.emplace_back( pt, -pt, -pt);
		verts.emplace_back(-pt, -pt, -pt);
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
	IndexedTriangleList GetTriangles() const
	{
		return
		{
			verts,{
				0,3,2,  0,2,1,  0,1,7,  7,6,1,
				1,2,5,  1,5,6,  3,2,4,  4,5,2,
				3,4,0,  0,4,7,  4,5,7,  7,6,5
				}
		};
	}

public:
	std::vector<Vec3> verts;
};