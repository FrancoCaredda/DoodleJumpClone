#include "Game.h"
#include "Physics.h"

#include "raylib.h"
#include "raymath.h"

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
		Vector2{ 0.5f, 0.5f },
		Vector2{ 0.5f, 0.5f },
		0.0f,
		&Spritesheet::Doodle1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0005f },
		true,
		EntityType::Character
	});

	m_Enitities.emplace_back(Entity{
		Vector2{ 0.5f, 0.95f },
		Vector2{ 0.5f, 0.5f },
		0.0f,
		&Spritesheet::Platform1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0 },
		true,
		EntityType::Platform
	});

	//for (int i = 0; i < 10; i++)
	//{
	//	m_Enitities.emplace_back(Entity{
	//		Vector2{ static_cast<float>(rand() % width) / width, static_cast<float>(rand() % height) / height },
	//		Vector2{ 0.5f, 0.5f },
	//		0.0f,
	//		&Spritesheet::Platform1,
	//		Vector2{ 0.0f, 0.0f },
	//		Vector2{ 0.0f, 0.0 },
	//		true,
	//		EntityType::Platform
	//	});
	//}

	
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{});

		UpdateLogic(GetFrameTime());
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

void Game::UpdateLogic(float deltaTime)
{
	bool collision = false;
	Vector2 movement = Vector2{ 0.0f, 0.0f };
	for (Entity& entity : m_Enitities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			ApplyGravity(entity, deltaTime);
			Update_Character(entity, deltaTime);
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
			collision = CheckCollision(entity, currentEntity, 1200, 900);
			break;
		}
	}

	if (collision)
	{
		entity.Velocity.y = -0.00035f;
	}	
}

Vector2 Game::GetMovement_Character()
{
	static Vector2 Right{ 0.5f, 0.0f };

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
