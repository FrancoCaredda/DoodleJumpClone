#include "Entity.h"

#include "raymath.h"

void ApplyGravity(Entity& entity, float deltaTime)
{
	if (!entity.bFalling)
	{
		return;
	}

	float gravity     = entity.Acceleration.y * deltaTime;
	float newVelocity = entity.Velocity.y + gravity;

	float newPosition = entity.Position.y + newVelocity;
	entity.Velocity.y = newVelocity;
	entity.Position.y = newPosition;
}

void ApplyMovement(Entity& entity, float direction, float deltaTime)
{
	float acceleration  = entity.Acceleration.x * deltaTime;
	float newVelocity   = entity.Velocity.x + acceleration;

	float newPosition   = entity.Position.x + direction * newVelocity;
	entity.Velocity.x   = newVelocity;
	entity.Position.x   = newPosition;
}

void ApplyBounciness(Entity& entity)
{
	if (entity.bBounce)
	{
		entity.Velocity.y = -std::sqrtf(entity.Acceleration.y * 2.0f * entity.BounceHeight);
	}
}

static Rectangle CalculateBoundingBox(const Entity& entity)
{
	return Rectangle{
		(entity.Position.x) - (entity.pSprite->Size.x * entity.Scale.x / 2.0f),
		(entity.Position.y) - (entity.pSprite->Size.y * entity.Scale.y / 2.0f),
		entity.pSprite->Size.x * entity.Scale.x,
		entity.pSprite->Size.y * entity.Scale.y
	};
}

bool CheckCollision(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.bSolid || !entity2.bSolid)
	{
		return false;
	}

	Rectangle BoundingBox1 = CalculateBoundingBox(entity1);
	Rectangle BoundingBox2 = CalculateBoundingBox(entity2);

	return CheckCollisionRecs(BoundingBox1, BoundingBox2);
}

bool HasEntityCollidedWithEntity(Entity& entity, const std::vector<Entity>& entities)
{
	for (const Entity& currentEntity : entities)
	{
		if (currentEntity.Type != entity.Type)
		{
			if (CheckCollision(entity, currentEntity))
			{
				return true;
			}
		}
	}

	return false;
}

void UpdateScroll(std::vector<Entity>& entities, float scroll)
{
	for (Entity& entity : entities)
	{
		entity.Position.y += scroll;
	}
}

// TODO: Introduce the concept of the scene/world
void UpdateCharacter(Entity& entity, const std::vector<Entity>& entities, uint32_t movementBound, float deltaTime)
{
	if (HasEntityCollidedWithEntity(entity, entities) && entity.Velocity.y > 0.0f)
	{
		ApplyBounciness(entity);
		entity.bBounce = false;
	}
	// HACK: Enable bouncing only if the velocity on the Y axis is greater than the threshold 
	// lest the character launch into the space
	entity.bBounce = entity.Velocity.y > 5.0f;
	
	if (IsKeyDown(KEY_D))
	{
		ApplyMovement(entity, 1, deltaTime);
	}
	else if (IsKeyDown(KEY_A))
	{
		ApplyMovement(entity, -1, deltaTime);
	}

	if (entity.Position.x > movementBound)
	{
		entity.Position.x = 0;
	}

	if (entity.Position.x < 0)
	{
		entity.Position.x = movementBound;
	}

}

void UpdatePlatform(Entity& platform, const Vector2& spawnPosition, uint32_t upperBound)
{
	if ((uint32_t)platform.Position.y > upperBound)
	{
		platform.Position.y = spawnPosition.y - (rand() % 50);
	}
}
