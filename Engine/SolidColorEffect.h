//#pragma once
//
//#include "Pipeline.h"
//
//class SolidColorEffect
//{
//public:
//	class Vertex
//	{
//	public:
//		Vec3 pos;
//	};
//	
//
//	// invoked for each pixel of a triangle
//	// takes an input of attributes that are the
//	// result of interpolating vertex attributes
//	// and outputs a color
//	class PixelShader
//	{
//	public:
//		template <typename Input>
//		Color operator()( Input& in )
//		{
//			return c;
//		}
//		void BindColor( Color c )
//		{
//			this->c = c;
//		}
//	private:
//		// prepare clamping constants
//		Color c;
//	};
//public:
//	PixelShader ps;
//
//};