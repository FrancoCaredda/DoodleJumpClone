#include "Renderer.h"

#include "raylib.h"

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
		Rectangle rect = entity.GetRectangle();

		DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, Color{ 255, 0, 0, 255 });
	}
}
