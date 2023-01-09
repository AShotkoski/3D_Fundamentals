#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Pipeline.h"
#include "GradiantColorEffect.h"
#include <algorithm>
#include <random>

class TwoCubeScene : public Scene
{
public:

	typedef Pipeline<GradiantColorEffect> Pipeline;
	typedef Pipeline::Vertex Vertex;

public:
	TwoCubeScene( Graphics& gfx )
		:
		Scene( "Dual cube scene" ),
		pipe( gfx )
	{
		std::vector<Color> vCols =
		{
			Colors::Coral,
			Colors::DarkGreen,
			Colors::DarkKhaki,
			Colors::DarkOrange,
			Colors::Maroon,
			Colors::GhostWhite,
			Colors::DarkViolet,
			Colors::DeepPink,
			Colors::Gold,
			Colors::HotPink,
			Colors::Khaki,
			Colors::Tomato,
			Colors::PeachPuff,
			Colors::Orange,
			Colors::OrangeRed,
			Colors::Teal,
			Colors::MediumAquamarine
		};

		std::mt19937 rng( std::random_device{}( ) );

		tlist0 = Cube::GetMinimumVerts<Vertex>();
		tlist1 = Cube::GetMinimumVerts<Vertex>(0.5f);

		//Set vert colors
		std::shuffle( vCols.begin(), vCols.end(), rng );

		std::for_each( tlist0.vertices.begin(), tlist0.vertices.end(),
			[&, i = 0]( Vertex& v ) mutable
			{
				v.color = Vec3(vCols[i++]);  //this invokes the colors operator vec3
			} 
		);

		std::shuffle( vCols.begin(), vCols.end(), rng );
		std::for_each( tlist1.vertices.begin(), tlist1.vertices.end(),
			[&, i = 0]( Vertex& v ) mutable
			{
				v.color = Vec3(vCols[i++]);  //this invokes the colors operator vec3
			} 
		);
		
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

		pipe.BindRotation( Mat3::RotationX( xRot ) * Mat3::RotationY( yRot ) * Mat3::RotationZ( zRot ) );
		pipe.BindTranslation( { 0.f,0.f,zOffset } );
		pipe.Draw( tlist0 );
		pipe.Draw( tlist1 );

	}

private:
	Pipeline pipe;
	IndexedTriangleList<Vertex> tlist0;
	IndexedTriangleList<Vertex> tlist1;
	const float dTheta = customUtil::math::PI / 4;
	float zOffset = 2.f;
	float xRot = 0.f;
	float yRot = 0.f;
	float zRot = 0.f;
};