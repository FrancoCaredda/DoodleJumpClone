#include "Game.h"

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
			collision = CheckCollision_Character(entity);
			movement = GetMovement_Character();
			Update_Character(entity, movement, collision, deltaTime);
			break;
		default:
			break;
		}
	}
}

void Game::Update_Character(Entity& entity, const Vector2& movementDirection, bool collision, float deltaTime)
{
	Vector2 newAcceleration = Vector2Add(entity.Acceleration, movementDirection);
	Vector2 currentAcceleration = Vector2Scale(newAcceleration, deltaTime);

	if (collision)
	{
		Vector2 newVelocity = Vector2Add(Vector2{ entity.Velocity.x, -0.25f }, currentAcceleration);
		Vector2 newPosition = Vector2Add(entity.Position, newVelocity);

		entity.Velocity = newVelocity;
		entity.Position = newPosition;
		return;
	}

	Vector2 newVelocity = Vector2Add(entity.Velocity, currentAcceleration);
	Vector2 newPosition = Vector2Add(entity.Position, newVelocity);

	entity.Velocity = newVelocity;
	entity.Position = newPosition;
}

bool Game::CheckCollision_Character(Entity& character)
{
	for (int i = 0; i < m_Enitities.size(); i++)
	{
		if (character.Type == m_Enitities[i].Type)
		{
			continue;
		}

		if (CheckCollisionRecs(character.GetRectangle(), m_Enitities[i].GetRectangle()) &&
			character.Solid && m_Enitities[i].Solid &&
			character.Position.y < m_Enitities[i].Position.y)
		{
			return true;
		}
	}

	return false;
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
