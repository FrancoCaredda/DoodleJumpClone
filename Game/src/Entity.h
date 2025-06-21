#pragma once

#include "Sprites.h"

#include "raylib.h"

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
};