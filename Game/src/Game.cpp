#include "Game.h"

#include "raylib.h"
#include "raymath.h"

#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <iostream>

void Game::Run()
{
	Init();
	RunLoop();
	Close();
}

void Game::Init()
{
	srand(time(0));

	InitWindow(m_Width, m_Height, "Doodle Jump Clone");
	SetTargetFPS(60);

	m_Spritesheet.Load("../../../../Assets/spritesheet.png");

	m_World.Init();
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		m_World.Update(GetFrameTime());
		m_Renderer.RenderFrame(m_World.GetEntities(), m_Spritesheet);
	}
}

void Game::Close()
{
	m_World.CleanUp();
	CloseWindow();
}
