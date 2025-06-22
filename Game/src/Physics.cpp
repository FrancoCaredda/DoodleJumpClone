#include "Physics.h"

#include "raymath.h"

void ApplyGravity(Entity& entity, float deltaTime)
{
	Vector2 newAcceleration = Vector2Scale(entity.Acceleration, deltaTime);
	Vector2 newVelocity = Vector2Add(entity.Velocity, newAcceleration);

	Vector2 newPosition = Vector2Add(entity.Position, newVelocity);

	entity.Velocity = newVelocity;
	entity.Position = newPosition;
}

static Rectangle CalculateBoundingBox(const Entity& entity, uint32_t width, uint32_t height)
{
	return Rectangle{
		(entity.Position.x * width) - (entity.pSprite->Size.x * entity.Scale.x / 2.0f),
		(entity.Position.y * height) - (entity.pSprite->Size.y * entity.Scale.y / 2.0f),
		entity.pSprite->Size.x* entity.Scale.x,
		entity.pSprite->Size.y* entity.Scale.y
	};
}

bool CheckCollision(const Entity& entity1, const Entity& entity2, uint32_t width, uint32_t height)
{
	if (!entity1.Solid || !entity2.Solid)
	{
		return false;
	}
	
	Rectangle BoundingBox1 = CalculateBoundingBox(entity1, width, height);
	Rectangle BoundingBox2 = CalculateBoundingBox(entity2, width, height);

	return CheckCollisionRecs(BoundingBox1, BoundingBox2);
}
