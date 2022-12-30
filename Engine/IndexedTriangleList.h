#pragma once
#include <vector>
#include "Vec3.h"

//vertices, indices
template <class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList( std::vector<T> verts, std::vector<size_t> inds )
		:
		vertices( std::move( verts ) ),
		indices( std::move( inds ) )
	{
		assert( vertices.size() > 2 );
		assert( indices.size() % 3 == 0 );
	}
	std::vector<T> vertices;
	std::vector<size_t> indices;
};