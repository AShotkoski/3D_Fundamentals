#pragma once
#include "Scene.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "SolidColorEffect.h"
#include "ObjLoader.h"

class DeerScene : public Scene
{
public:

	typedef Pipeline<SolidColorEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;

public:
	DeerScene( Graphics& gfx )
		:
		Scene( "deer sceme" ),
		pipe( gfx )
	{
		//Load file
		//TODO take file path as deerscene param
		if ( !loader.LoadFile( "objects\\deer.obj" ) )
		{
			throw std::runtime_error( "can't find monky obj file" );
		}
		tlist.vertices.reserve( loader.LoadedVertices.size() );
		tlist.indices.reserve( loader.LoadedIndices.size() );

		//this could be better but idc
		for ( const auto& v : loader.LoadedVertices )
		{
			tlist.vertices.emplace_back( Vec3( v.Position.X, v.Position.Y, v.Position.Z ) );
		}
		for ( const auto& i : loader.LoadedIndices )
		{
			tlist.indices.emplace_back( i );
		}


		
		pipe.effect.ps.BindColor( Colors::Gray );



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
			zOffset += dt * zMoveSpeed;
		}
		if ( kbd.KeyIsPressed( 'F' ) )
		{
			zOffset -= dt * zMoveSpeed;
		}

	}

	void Draw() override
	{
		


		pipe.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist );

	}

private:
	Pipeline pipe;
	objl::Loader loader;
	IndexedTriangleList<Vertex> tlist;
	const float dTheta = customUtil::math::PI / 4;
	float zOffset = 3500.f;
	float zMoveSpeed = 2000.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};