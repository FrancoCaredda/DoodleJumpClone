#include "Renderer.h"

#include "raylib.h"

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
		entity.Rotation,
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

void Renderer::RenderFrame(const std::vector<Entity>& entities, const Spritesheet& spritesheet)
{
	BeginDrawing();
	ClearBackground(Color{});

	RenderBackground();
	RenderEntities(entities, spritesheet);
	RenderRectangles(entities);
	DrawFPS(0, 0);

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
