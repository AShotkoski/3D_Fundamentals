#pragma once

template <class V>
class Triangle
{
public:
	Triangle() = default;
	Triangle(V v0_, V v1_, V v2_)
		:
		v0(v0_),
		v1(v1_),
		v2(v2_)
	{ }
	
public:
	V v0;
	V v1;
	V v2;
};