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

	m_Enitities.reserve(10);

	m_Enitities.emplace_back(Entity{
		Vector2{ 600, 450 },
		Vector2{ 0.5f, 0.5f },
		&Spritesheet::Doodle1,
		Vector2{ 10.0f, 0.0f },
		Vector2{ 0.0f, 40.0f },
		20.0f,
		true,
		true,
		true,
		EntityType::Character
	});


	m_Enitities.emplace_back(Entity{
		Vector2{ 600, 800 },
		Vector2{ 0.5f, 0.5f },
		&Spritesheet::Platform1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0 },
		0.0f,
		true,
		false,
		false,
		EntityType::Platform
	});

	for (int i = 0; i < 9; i++)
	{
		m_Enitities.emplace_back(Entity{
			Vector2{ static_cast<float>(rand() % m_Width), static_cast<float>(rand() % m_Height) },
			Vector2{ 0.5f, 0.5f },
			&Spritesheet::Platform1,
			Vector2{ 0.0f, 0.0f },
			Vector2{ 0.0f, 0.0 },
			0.0f,
			true,
			false,
			false,
			EntityType::Platform
		});
	}
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		UpdateLogic(GetFrameTime());
		m_Renderer.RenderFrame(m_Enitities, m_Spritesheet);
	}
}

void Game::Close()
{
	CloseWindow();
}

void Game::UpdateLogic(float deltaTime)
{
	static Vector2 position{};
	static Vector2 velocity{};


	if (position.y < m_Height / 2.0f && velocity.y < 0)
	{
		m_Scroll += -velocity.y * 1.75f * deltaTime;
	}
	else
	{
		m_Scroll = 0;
	}

	UpdateScroll(m_Enitities, m_Scroll);

	for (Entity& entity : m_Enitities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			position = entity.Position;
			velocity = entity.Velocity;
			ApplyGravity(entity, deltaTime);
			UpdateCharacter(entity, m_Enitities, m_Width, deltaTime);
			break;
		case EntityType::Platform:
			UpdatePlatform(entity, position, m_Height);
			break;
		default:
			break;
		}
	}
}

