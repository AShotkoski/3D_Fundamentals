#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "TextureEffect.h"

class SkinTexCube : public Scene
{
	
public:	
	typedef Pipeline<TextureEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;
public:
	SkinTexCube(Graphics& gfx, std::wstring textureFilePath)
		:
		Scene( "Minecraft grass block scene" ),
		tlist(Cube::GetSkinned<Vertex>(1.f)),
		pipe(gfx)
	{
		pipe.effect.ps.BindTexture( textureFilePath );
	}
	void Update( Keyboard& kbd, Mouse& mouse, float dt ) override
	{
		using namespace customUtil::math;

		pipe.BeginFrame();

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
	void Draw( ) override
	{
		pipe.effect.vs.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.effect.vs.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist );

	}
	
private:	
	Pipeline pipe;
	IndexedTriangleList<Vertex> tlist;

	const float dTheta = customUtil::math::PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};