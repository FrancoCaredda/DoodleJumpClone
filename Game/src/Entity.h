#pragma once

#include "Sprites.h"

#include "raylib.h"

#include <vector>

enum class EntityType : uint8_t
{
	None = 0,
	Character = 1,
	Platform = 2,

	MAX
};

struct Entity
{
	// Transform
	Vector2 Position;
	Vector2 Scale;
	float Rotation;

	// Rendering
	const Sprite* pSprite;

	// Physics
	Vector2 Velocity;
	Vector2 Acceleration;
	float Solid;

	// Game Logic
	EntityType Type;

	inline Rectangle GetRectangle() const
	{
		return Rectangle{
			Position.x - pSprite->Size.x * Scale.x / 2.0f, Position.y - pSprite->Size.y * Scale.y / 2.0f ,
			pSprite->Size.x * Scale.x, pSprite->Size.y * Scale.y 
		};
	}
};

void UpdateLogic(std::vector<Entity>& entities, float deltaTime);