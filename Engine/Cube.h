#pragma once
#include "Vec3.h"
#include <vector>
#include "IndexedLineList.h"

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

public:
	std::vector<Vec3> verts;
};