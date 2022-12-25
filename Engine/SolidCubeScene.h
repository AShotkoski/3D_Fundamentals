#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"

class SolidCubeScene : public Scene
{
public:
	SolidCubeScene() = default;
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
		Color cols[12] =
		{
			Colors::White,
			Colors::Blue,
			Colors::Cyan,
			Colors::Gray,
			Colors::Green,
			Colors::LightGray,
			Colors::Magenta,
			Colors::Red,
			Colors::White,
			Colors::Yellow,
			Colors::Green,
			Colors::Red
		};


		auto tris = cube.GetTriangles();
		const auto rot = Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot );
		//Transform verticies from object space to world/view space
		for ( auto& v : tris.verticies )
		{
			v *= rot;
			v += {0.f, 0.f, zOffset};
		}

		//Set cull flags
		for ( int i = 0; i < tris.indicies.size() / 3; i++ )
		{
			const Vec3& v0 = (Vec3)tris.verticies[tris.indicies[i * 3]];
			const Vec3& v1 = (Vec3)tris.verticies[tris.indicies[i * 3 + 1]];
			const Vec3& v2 = (Vec3)tris.verticies[tris.indicies[i * 3 + 2]];
			tris.cullFlags[i] = v0 * ( v1 - v0 ).Cross( ( v2 - v0 ) ) <= 0.f;
		}


		//Transform to screen space
		for ( auto& v : tris.verticies )
		{
			pube.Transform( v );
		}

		//draw the triangles (cube)
		for ( int i = 0; i < tris.indicies.size(); i += 3 )
		{
			//skip back-facing triangles
			if ( tris.cullFlags[i / 3] )
			{
				gfx.DrawTriangle( tris.verticies[tris.indicies[i]],
					tris.verticies[tris.indicies[i + 1]],
					tris.verticies[tris.indicies[i + 2]],
					cols[i / 3] );

			}
		}

	}
	
private:	
	PubeScreenTransformer pube;
	Cube cube = (1.f);

	const float dTheta = PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};