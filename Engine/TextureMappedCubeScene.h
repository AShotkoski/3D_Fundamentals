#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"

class TextureMappedCubeScene : public Scene
{
public:
	TextureMappedCubeScene()
	{

	};
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
		const float size = .5f;
		auto tris = IndexedTriangleList<TextureVertex>{
			{
				TextureVertex{{-size, size, zOffset}, {0.f,1.f}}, TextureVertex{{size, size, zOffset}, {1.f,1.f}},
				TextureVertex{{size, -size, zOffset}, {1.f,0.f}}, TextureVertex{{-size, -size, zOffset}, {0.f,0.f}}
			}, {0,1,2, 0,2,3 }
		};

		const auto rot = Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot );

		//Transform verticies from object space to world/view space
		for ( auto& v : tris.verticies )
		{
			v.pos *= rot;
			v.pos += {0.f, 0.f, zOffset};
		}


		//Transform to screen space
		for ( auto& v : tris.verticies )
		{
			pube.Transform( v.pos );
		}

		//draw the mf
		for ( size_t i = 0; i < tris.indicies.size(); i += 3 )
		{		
			gfx.DrawTriangleTex( tris.verticies[tris.indicies[i]],
				tris.verticies[tris.indicies[i + 1]],
				tris.verticies[tris.indicies[i + 2]],
				tex );
		}
	}

private:
	PubeScreenTransformer pube;
	Cube cube = ( 1.f );

	const float dTheta = PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;

	Surface tex = Surface::FromFile(L"sprites\\test.png");
};