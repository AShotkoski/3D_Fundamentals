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
	auto lines = cube.GetLines();
	const auto rot = Mat3::RotationX(xRot) * Mat3::RotationY(yRot) * Mat3::RotationZ( zRot ) ;
	for ( auto& v : lines.verticies )
	{
		v *= rot;
		v += {0.f, 0.f, zOffset};
		pube.Transform( v );
	}
	for ( auto i = lines.indicies.cbegin(), end = lines.indicies.cend(); i != end; std::advance( i, 2 ) )
	{
		gfx.DrawLine( lines.verticies[*i], lines.verticies[ *( std::next(i) ) ], Colors::White );
	}
}