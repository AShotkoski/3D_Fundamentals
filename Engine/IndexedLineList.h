#pragma once
#include <vector>
#include "Vec3.h"

//verticies, indicies
struct IndexedLineList
{
	std::vector<Vec3> verticies;
	std::vector<size_t> indicies;
};