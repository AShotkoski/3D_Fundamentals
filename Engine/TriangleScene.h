#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "GradiantColorEffect.h"

//basic triangle scene for testing different shaders
class TriangleScene : public Scene
{
public:

	typedef Pipeline<GradiantColorEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;

public:
	TriangleScene( Graphics& gfx )
		:
		Scene( "Triangle Scene" ),
		pipe( gfx )
	{
	}

	void Update( Keyboard& kbd, Mouse& mouse, float dt ) override
	{
		using namespace customUtil::math;

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
				{Vec3{0.f,1.f,zOffset}, Vec3{Colors::Red}},
				{Vec3{0.5f,0.5f,zOffset}, Vec3{Colors::Green}},
				{Vec3{-0.5f,-0.5f,zOffset}, Vec3{Colors::Blue}},
			}	,
			{0,1,2}
		};
		

		pipe.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist );

	}

private:
	

	Pipeline pipe;
	const float dTheta = customUtil::math::PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};