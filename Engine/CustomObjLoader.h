#pragma once
#include "ObjLoader.h"
#include "IndexedTriangleList.h"

namespace customUtil
{
	namespace obj
	{
		template<class Vertex>
		IndexedTriangleList<Vertex> LoadObj( std::string filePath )
		{
			objl::Loader loader;

			if ( !loader.LoadFile( filePath ) )
			{
				throw std::runtime_error( "Couldn't open obj file " + filePath );
			}

			IndexedTriangleList<Vertex> tlist;

			tlist.vertices.reserve( loader.LoadedVertices.size() );
			tlist.indices.reserve( loader.LoadedIndices.size() );


			for ( const auto& v : loader.LoadedVertices )
			{
				tlist.vertices.emplace_back( Vec3( v.Position.X, v.Position.Y, v.Position.Z ) );
			}
			for ( const auto& i : loader.LoadedIndices )
			{
				tlist.indices.emplace_back( i );
			}

			return tlist; //this should use move semantics i think

		}
	};
};