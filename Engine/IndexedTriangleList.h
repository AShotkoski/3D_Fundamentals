#pragma once
#include <vector>
#include "Vec3.h"
#include "Miniball.hpp"

//vertices, indices
template <class V>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList( std::vector<V> verts, std::vector<size_t> inds )
		:
		vertices( std::move( verts ) ),
		indices( std::move( inds ) )
	{
		assert( vertices.size() > 2 );
		assert( indices.size() % 3 == 0 );
	}

	void MakeCentered()
	{
		//I understand it as I need a coordaccessor to 
		//hold iterators to the points and coords,
		//which is a functor that, when envoked gives a ptr
		//to the first (in memory) coordinate
		struct VertAccessor
		{
			typedef std::vector<V>::const_iterator Pit;
			typedef const float* Cit;
			Cit operator()(Pit it) const
			{
				return &it->pos.x;
			}
		};

		Miniball::Miniball<VertAccessor> mb( 3, vertices.begin(), vertices.end() );
		const auto pCent = mb.center();

		const Vec3 center = { *pCent, *std::next( pCent ),*std::next( pCent, 2 ) };

		for ( auto& v : vertices )
		{
			v.pos -= center;
		}
	}


	//core data
	std::vector<V> vertices;
	std::vector<size_t> indices;
};