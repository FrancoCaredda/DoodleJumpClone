#include "Entity.h"

#include "raymath.h"

static void Update_Character(Entity& entity, bool collision, float deltaTime)
{
	if (collision)
	{
		Vector2 acceleration = Vector2Scale(entity.Acceleration, deltaTime);
		Vector2 newVelocity = Vector2Add(Vector2{ entity.Velocity.x, -0.25f }, acceleration);
		
		Vector2 newPosition = Vector2Add(entity.Position, newVelocity);
		
		entity.Velocity = newVelocity;
		entity.Position = newPosition;
		return;
	}

	Vector2 acceleration = Vector2Scale(entity.Acceleration, deltaTime);
	Vector2 newVelocity = Vector2Add(entity.Velocity, acceleration);

	Vector2 newPosition = Vector2Add(entity.Position, newVelocity);

	entity.Velocity = newVelocity;
	entity.Position = newPosition;
}

static bool CheckCollision_Character(Entity& character, const std::vector<Entity>& entities)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (character.Type == entities[i].Type)
		{
			continue;
		}

		if (CheckCollisionRecs(character.GetRectangle(), entities[i].GetRectangle()) &&
			character.Solid && entities[i].Solid &&
			character.Position.y < entities[i].Position.y)
		{
			return true;
		}
	}

	return false;
}

void UpdateLogic(std::vector<Entity>& entities, float deltaTime)
{
	bool collision = false;
	for (Entity& entity : entities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			collision = CheckCollision_Character(entity, entities);
			Update_Character(entity, collision, deltaTime);
			break;
		default:
			break;
		}
	}
}
