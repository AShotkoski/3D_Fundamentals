#pragma once
#include "Mat3.h"

template <class Vertex>
class DefaultVertexShader
{
public:
	typedef Vertex OutputVertex;
public:
	void BindRotation( const Mat3& rotation_in )
	{
		rotation = rotation_in;
	}

	void BindTranslation( const Vec3& translation_in )
	{
		translation = translation_in;
	}

	OutputVertex operator()(const Vertex& v) const
	{
		// transform vertices using matrix + vector
		return { v.pos * rotation + translation, v };
	}

private:
	Mat3 rotation = Mat3::Identity();
	Vec3 translation;
};