#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"

class WireframeCubeScene : public Scene
{
public:
	WireframeCubeScene() = default;
	void Update( Keyboard& kbd, Mouse& mouse, float dt ) override
	{
		if ( kbd.KeyIsPressed( 'Q' ) )
		{
			zRot = (float)ClampAngle( zRot + dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'E' ) )
		{
			zRot = (float)ClampAngle( zRot - dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'D' ) )
		{
			yRot = (float)ClampAngle( yRot + dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'A' ) )
		{
			yRot = (float)ClampAngle( yRot - dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'W' ) )
		{
			xRot = (float)ClampAngle( xRot + dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'S' ) )
		{
			xRot = (float)ClampAngle( xRot - dt * dTheta );
		}
		if ( kbd.KeyIsPressed( 'R' ) )
		{
			zOffset += dt;
		}
		if ( kbd.KeyIsPressed( 'F' ) )
		{
			zOffset -= dt;
		}

	}
	void Draw( Graphics& gfx ) const override
	{

		auto lines = cube.GetLines();
		const auto rot = Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot );

		//Transform verticies from object space to world/view space
		for ( auto& v : lines.verticies )
		{
			v *= rot;
			v += {0.f, 0.f, zOffset};
		}


		//Transform to screen space
		for ( auto& v : lines.verticies )
		{
			pube.Transform( v );
		}

		//draw the triangles (cube)
		for ( int i = 0; i < lines.indicies.size(); i += 2 )
		{
			gfx.DrawLine( lines.verticies[lines.indicies[i]],
							  lines.verticies[lines.indicies[i + 1]],
				Colors::Red );
	
		}

	}

private:
	PubeScreenTransformer pube;
	Cube cube = Cube( 1.f, 1.f );

	const float dTheta = PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};