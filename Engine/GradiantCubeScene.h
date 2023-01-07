#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "GradiantColorEffect.h"


class GradiantCubeScene : public Scene
{
public:

	typedef Pipeline<GradiantColorEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;

public:
	GradiantCubeScene( Graphics& gfx )
		:
		Scene( "Gradiant Cube Scene" ),
		pipe( gfx )
	{
		tlist = Cube::GetMinimumVerts<Vertex>();
	}

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

	void Draw() override
	{
		tlist.vertices[0].color = { 255,0,0 };
		tlist.vertices[1].color = { 255,255,0 };
		tlist.vertices[2].color = { 255,0,255 };
		tlist.vertices[3].color = { 0,0,255 };
		tlist.vertices[4].color = { 0,255,0 };
		tlist.vertices[5].color = { 127,127,0 };
		tlist.vertices[6].color = { 0,125,57 };
		tlist.vertices[7].color = { 255,0,127 };

		

		pipe.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist );

	}

private:
	Pipeline pipe;
	IndexedTriangleList<Vertex> tlist;
	const float dTheta = PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};