#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "SolidColorEffect.h"

class TriangleScene : public Scene
{
public:

	typedef Pipeline<SolidColorEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;
public:
	TriangleScene( Graphics& gfx )
		:
		Scene( "Triangle Scene" ),
		pipe( gfx )
	{
		pipe.effect.ps.BindColor( Colors::Green );
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
		IndexedTriangleList<Vertex> tlist{
			{
				Vec3{0.f,1.f,zOffset},
				Vec3{0.5f,0.5f,zOffset},
				Vec3{-0.5f,-0.5f,zOffset} 
			}	,
			{0,1,2}
		};
		

		pipe.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist );

	}

private:
	Pipeline pipe;
	SolidColorEffect tEffect;
	const float dTheta = PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};