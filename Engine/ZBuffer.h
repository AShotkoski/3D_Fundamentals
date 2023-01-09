#pragma once
#include <limits>
#include <vector>


class ZBuffer
{
public:
	typedef unsigned int u_int;
public:
	ZBuffer(u_int width, u_int height)
		:
		width(width),
		height(height)
	{
		//set buffer size and clear
		pixelDepths.resize( width * height, 
			std::numeric_limits<float>::infinity() );
	}

	void Clear()
	{
		std::fill( pixelDepths.begin(), pixelDepths.end(), std::numeric_limits<float>::infinity() );
	}

	const float& at( u_int x, u_int y ) const
	{
		return pixelDepths[y * width + x];
	}

	//return true if supplied x,y is lowest (to be drawn)
	bool set_query( u_int x, u_int y, float val )
	{
		auto curval = at( x, y );

		if ( val < curval )
		{
			set( x, y, val );
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	void set( u_int x, u_int y, float val )
	{
		pixelDepths.at(y * width + x) = val;
	}
private:
	u_int width;
	u_int height;
	std::vector<float> pixelDepths;
};