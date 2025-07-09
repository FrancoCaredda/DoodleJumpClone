#include "Renderer.h"

#include "raylib.h"

#include <string>

void Renderer::RenderBackground()
{
	if (!IsRenderTextureValid(m_BackgroundFramebuffer))
	{
		BakeBackground();
	}

	DrawTexture(m_BackgroundFramebuffer.texture, 0, 0, RAYWHITE);
}

void Renderer::RenderEntity(const Entity& entity, const Spritesheet& spritesheet)
{
	DrawTexturePro(
		spritesheet.GetTexture(),
		Rectangle{ entity.pSprite->Offset.x, entity.pSprite->Offset.y,
				   entity.pSprite->Size.x, entity.pSprite->Size.y },
		Rectangle{ entity.Position.x, entity.Position.y,
				  entity.pSprite->Size.x * entity.Scale.x, entity.pSprite->Size.y * entity.Scale.y },
		Vector2{ entity.pSprite->Size.x * entity.Scale.x / 2.0f, entity.pSprite->Size.y * entity.Scale.y / 2.0f },
		0,
		RAYWHITE
	);
}

void Renderer::RenderEntities(const std::vector<Entity>& entities, const Spritesheet& spritesheet)
{
	for (const Entity& entity : entities)
	{
		RenderEntity(entity, spritesheet);
	}
}

void Renderer::RenderRectangles(const std::vector<Entity>& entities)
{
	for (const Entity& entity : entities)
	{
		DrawRectangleLines(
			(entity.Position.x) - (entity.pSprite->Size.x * entity.Scale.x / 2.0f),
			(entity.Position.y) - (entity.pSprite->Size.y * entity.Scale.y / 2.0f),
			entity.pSprite->Size.x * entity.Scale.x,
			entity.pSprite->Size.y * entity.Scale.y,
			Color{ 255, 0, 0, 255 }
		);
	}
}

void Renderer::RenderFrame(const std::vector<Entity>& entities, int score, const Spritesheet& spritesheet)
{
	BeginDrawing();
	ClearBackground(Color{});

	RenderBackground();
	RenderEntities(entities, spritesheet);
#ifdef _DEBUG
	RenderRectangles(entities);
#endif // _DEBUG


	std::string scoreString = "Your score: " + std::to_string(score);
	DrawText(scoreString.c_str(), 5, 15, 24, Color{ 0, 0, 0, 255 });

	EndDrawing();
}

void Renderer::RenderGameOverScreen()
{
	BeginDrawing();
	ClearBackground(Color{ 255, 255, 255, 255 });
	DrawText("You've lost", m_FramebufferWidth / 2 - 6 * 24 / 2, m_FramebufferHeight / 2 - 12, 24, Color{ 0, 0, 0, 255 });
	DrawText("Press any key to continue", m_FramebufferWidth / 2 - 13 * 24 / 2, m_FramebufferHeight / 2 + 12, 24, Color{ 0, 0, 0, 255 });
	EndDrawing();
}

void Renderer::BakeBackground()
{
	m_BackgroundFramebuffer = LoadRenderTexture(m_FramebufferWidth, m_FramebufferHeight);
	
	BeginTextureMode(m_BackgroundFramebuffer);
	ClearBackground(RAYWHITE);
	
	uint32_t xOffset = m_FramebufferWidth / m_BackgroundLinesCount;
	uint32_t yOffset = m_FramebufferHeight / m_BackgroundLinesCount;

	for (uint32_t i = 0; i < m_BackgroundLinesCount; i++)
	{
		DrawLine(xOffset * (i + 1), 0, xOffset * (i + 1), m_FramebufferHeight, Color{ 0, 0, 0, 45 });
		DrawLine(0, yOffset * (i + 1), m_FramebufferWidth, yOffset * (i + 1), Color{ 0, 0, 0, 45 });
	}

	EndTextureMode();
}
