/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat3.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cube(1.f)
{
	
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = 1.f / 144.f;

	if ( wnd.kbd.KeyIsPressed( 'Q' ) )
	{
		zRot =  (float)ClampAngle( zRot + dt * dTheta);
	}
	if ( wnd.kbd.KeyIsPressed( 'E' ) )
	{
		zRot = (float)ClampAngle( zRot - dt * dTheta );
	}
	if ( wnd.kbd.KeyIsPressed( 'D' ) )
	{
		yRot =  (float)ClampAngle( yRot + dt * dTheta);
	}
	if ( wnd.kbd.KeyIsPressed( 'A' ) )
	{
		yRot = (float)ClampAngle( yRot - dt * dTheta );
	}
	if ( wnd.kbd.KeyIsPressed( 'W' ) )
	{
		xRot =  (float)ClampAngle( xRot + dt * dTheta);
	}
	if ( wnd.kbd.KeyIsPressed( 'S' ) )
	{
		xRot = (float)ClampAngle( xRot - dt * dTheta );
	}
	if ( wnd.kbd.KeyIsPressed( 'R' ) )
	{
		zOffset += dt ;
	}
	if ( wnd.kbd.KeyIsPressed( 'F' ) )
	{
		zOffset -= dt ;
	}

}

void Game::ComposeFrame()
{
	Color cols[12] =
	{
		Colors::Black,
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
	//Transform verticies
	for ( auto& v : tris.verticies )
	{
		v *= rot;
		v += {0.f, 0.f, zOffset};
	}

	//Set cull flags
	for ( int i = 0; i < tris.indicies.size() / 3; i++)
	{
		const Vec3& v0 = (Vec3)tris.verticies[tris.indicies[i * 3] ];
		const Vec3& v1 = (Vec3)tris.verticies[tris.indicies[i * 3 + 1]];
		const Vec3& v2 = (Vec3)tris.verticies[tris.indicies[i * 3 + 2]];
		tris.cullFlags[i] = v0 * ( v1 - v0 ).Cross( ( v2 - v0 ) ) <= 0.f;
	}


	//Transform to pube space
	for ( auto& v : tris.verticies )
	{
		pube.Transform( v );
	}

	for ( int i = 0; i < tris.indicies.size(); i += 3 )
	{
		if ( tris.cullFlags[i / 3] )
		{
			gfx.DrawTriangle( tris.verticies[tris.indicies[i]],
				tris.verticies[tris.indicies[i + 1]],
				tris.verticies[tris.indicies[i + 2]],
				cols[i / 3] );

		}
	}

}