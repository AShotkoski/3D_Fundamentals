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
#include "SkinTexCube.h"
#include "TriangleScene.h"
#include "GradiantCubeScene.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	scenes.emplace_back( std::make_unique<SkinTexCube>(gfx) );
	scenes.emplace_back( std::make_unique<GradiantCubeScene>(gfx) );
	scenes.emplace_back( std::make_unique<TriangleScene>(gfx) );
	currScene = scenes.begin();
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

	while ( !wnd.kbd.KeyIsEmpty() )
	{
		auto e = wnd.kbd.ReadKey();

		if(e.GetCode() == VK_TAB && e.IsPress() )
		{
			
			CycleScenes( wnd.kbd.KeyIsPressed( VK_SHIFT ) ? true : false);
		}
		
	}

	( *currScene )->Update( wnd.kbd, wnd.mouse, dt );
	
}

void Game::CycleScenes(bool backwards)
{
	if ( !backwards )
	{
		if ( ++currScene == scenes.end() )
		{
			currScene = scenes.begin();
		}
	}
	else
	{
		if ( currScene == scenes.begin() )
		{
			currScene = std::prev(scenes.end());
		}
		else
		{
			--currScene;
		}
	}
	OutputDebugStringA( ( *currScene )->GetName().c_str() );
	OutputDebugStringA( "\n" );
}

void Game::ComposeFrame()
{
	( *currScene )->Draw( );
}