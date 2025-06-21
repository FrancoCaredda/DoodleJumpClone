#include "Game.h"

#include "raylib.h"

#include <cstdint>

void Game::Run()
{
	Init();
	RunLoop();
	Close();
}

void Game::Init()
{
	uint32_t width = 1200;
	uint32_t height = 900;

	InitWindow(width, height, "Doodle Jump Clone");
	m_Spritesheet.Load("../../../../Assets/spritesheet.png");

	m_Enitities.reserve(10);

	m_Enitities.emplace_back(Entity{
		Vector2{ width / 2.0f, height / 2.0f },
		Vector2{ 0.5f, 0.5f },
		0.0f,
		&Spritesheet::Doodle1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0f },
		true,
		EntityType::Character
	});
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{});

		Entity& player = m_Enitities[0];

		DrawTexturePro(
			m_Spritesheet.GetTexture(),
			Rectangle{ player.pSprite->Offset.x, player.pSprite->Offset.y, 
					   player.pSprite->Size.x, player.pSprite->Size.y },
			Rectangle{ player.Position.x, player.Position.y, 
					  player.pSprite->Size.x * player.Scale.x, player.pSprite->Size.y * player.Scale.y },
			Vector2{ player.pSprite->Size.x * player.Scale.x / 2.0f, player.pSprite->Size.y * player.Scale.y / 2.0f },
			player.Rotation,
			RAYWHITE
		);

		EndDrawing();
	}
}

void Game::Close()
{
	CloseWindow();
}
