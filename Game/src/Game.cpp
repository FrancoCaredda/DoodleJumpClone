#include "Game.h"

#include "raylib.h"

#include <cstdint>
#include <cstdlib>

void Game::Run()
{
	Init();
	RunLoop();
	Close();
}

void Game::Init()
{
	srand(time(0));

	uint32_t width = 1200;
	uint32_t height = 900;

	InitWindow(width, height, "Doodle Jump Clone");
	m_Spritesheet.Load("../../../../Assets/spritesheet.png");

	m_Enitities.reserve(10);

	m_Enitities.emplace_back(Entity{
		Vector2{ width / 2.0f, 0.0f },
		Vector2{ 0.5f, 0.5f },
		0.0f,
		&Spritesheet::Doodle1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.5f },
		true,
		EntityType::Character
	});

	for (int i = 0; i < 10; i++)
	{
		m_Enitities.emplace_back(Entity{
			Vector2{ static_cast<float>(rand() % width), static_cast<float>(rand() % height) },
			Vector2{ 0.5f, 0.5f },
			0.0f,
			&Spritesheet::Platform1,
			Vector2{ 0.0f, 0.0f },
			Vector2{ 0.0f, 0.0 },
			true,
			EntityType::Platform
		});
	}

	
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{});

		UpdateLogic(m_Enitities, GetFrameTime());
		m_Renderer.RenderBackground();
		m_Renderer.RenderEntities(m_Enitities, m_Spritesheet);
		m_Renderer.RenderRectangles(m_Enitities);
		DrawFPS(0, 0);

		EndDrawing();
	}
}

void Game::Close()
{
	CloseWindow();
}
