#include "Game.h"
#include "Physics.h"

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
		0.0f,
		&Spritesheet::Doodle1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 40.0f },
		true,
		EntityType::Character
	});


	m_Enitities.emplace_back(Entity{
		Vector2{ 600, 800 },
		Vector2{ 0.5f, 0.5f },
		0.0f,
		&Spritesheet::Platform1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0 },
		true,
		EntityType::Platform
	});

	for (int i = 0; i < 9; i++)
	{
		m_Enitities.emplace_back(Entity{
			Vector2{ static_cast<float>(rand() % m_Width), static_cast<float>(rand() % m_Height) },
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
	bool collision = false;
	Vector2 movement = Vector2{ 0.0f, 0.0f };

	Entity* player = nullptr;

	for (Entity& entity : m_Enitities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			ApplyGravity(entity, deltaTime);
			Update_Character(entity, deltaTime);
			player = &entity;
			break;
		case EntityType::Platform:
			if (player)
			{
				Update_Platform(entity, *player, deltaTime);
			}
			break;
		default:

			break;
		}
	}
}

void Game::Update_Character(Entity& entity, float deltaTime)
{
	bool collision = false;
	for (const Entity& currentEntity : m_Enitities)
	{
		if (currentEntity.Type != entity.Type)
		{
			if (collision = CheckCollision(entity, currentEntity, 1200, 900))
			{
				break;
			}
		}
	}

	Vector2 direction = GetMovement_Character();
	entity.Acceleration.x = direction.x;

	if (collision)
	{
		//					acceleration * 2.0f * height
		entity.Velocity.y = -std::sqrtf(entity.Acceleration.y * 2.0f * 10.0f);
	}

	if (entity.Position.x > m_Width)
	{
		entity.Position.x = 0;
	}
	
	if (entity.Position.x < 0)
	{
		entity.Position.x = m_Width;
	}

	if (entity.Position.y < m_Height / 2.0f && entity.Velocity.y < 0)
	{
		m_PlatformScroll += -entity.Velocity.y * deltaTime;
		entity.Position.y += m_PlatformScroll;
	}
	else
	{
		m_PlatformScroll = 0;
	}
}

void Game::Update_Platform(Entity& platform, const Entity& player, float deltaTime)
{
	platform.Position.y += m_PlatformScroll;

	if (platform.Position.y > m_Height)
	{
		platform.Position.y = player.Position.y - (rand() % 150);
	}
}

Vector2 Game::GetMovement_Character()
{
	static Vector2 Right{ 30.0f, 0.0f };

	if (IsKeyDown(KEY_D))
	{
		return Right;
	}
	if (IsKeyDown(KEY_A))
	{
		return Vector2Scale(Right, -1);
	}

	return Vector2Scale(Right, 0.0f);
}
