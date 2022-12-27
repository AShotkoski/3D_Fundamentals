#pragma once
#include <vector>
#include "Vec3.h"

//verticies, indicies
template <class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList( std::vector<T> verts, std::vector<size_t> inds )
		:
		verticies( std::move( verts ) ),
		indicies( std::move( inds ) )
	{
		assert( verticies.size() > 2 );
		assert( indicies.size() % 3 == 0 );
		cullFlags.resize( indicies.size() / 3, false );
	}
	std::vector<T> verticies;
	std::vector<size_t> indicies;
	std::vector<bool> cullFlags;
};