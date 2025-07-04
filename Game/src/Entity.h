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

	// Rendering
	const Sprite* pSprite;

	// Physics
	Vector2 Velocity;
	Vector2 Acceleration;

	float BounceHeight;

	uint8_t bSolid   : 1;
	uint8_t bFalling : 1;
	uint8_t bBounce  : 1;

	// Game Logic
	EntityType Type;
};

void ApplyGravity(Entity& entity, float deltaTime);
void ApplyMovement(Entity& entity, float direction, float deltaTime);
void ApplyBounciness(Entity& entity);

bool CheckCollision(const Entity& entity1, const Entity& entity2);

bool HasEntityCollidedWithEntity(Entity& entity, const std::vector<Entity>& entities);

void UpdateScroll(std::vector<Entity>& entities, float scroll);
void UpdateCharacter(Entity& entity, const std::vector<Entity>& entities, uint32_t movementBound, float deltaTime);
void UpdatePlatform(Entity& platform, const Vector2& spawnPosition, uint32_t upperBound);

