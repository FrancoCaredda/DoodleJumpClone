#include "Entity.h"

#include "raymath.h"

static Vector2 GetMovement_Character()
{
	static Vector2 Right{0.5f, 0.0f};
	
	if (IsKeyDown(KEY_D))
	{
		return Right;
	}
	if (IsKeyDown(KEY_A))
	{
		return Vector2Scale(Right, -1);
	}

	return Vector2Scale(Right, 0.0f);
}

static void Update_Character(Entity& entity, const Vector2& movementDirection, bool collision, float deltaTime)
{
	Vector2 newAcceleration = Vector2Add(entity.Acceleration, movementDirection);
	Vector2 currentAcceleration = Vector2Scale(newAcceleration, deltaTime);

	if (collision)
	{
		Vector2 newVelocity = Vector2Add(Vector2{ entity.Velocity.x, -0.25f }, currentAcceleration);
		Vector2 newPosition = Vector2Add(entity.Position, newVelocity);
		
		entity.Velocity = newVelocity;
		entity.Position = newPosition;
		return;
	}

	Vector2 newVelocity = Vector2Add(entity.Velocity, currentAcceleration);
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
	Vector2 movement = Vector2{ 0.0f, 0.0f };
	for (Entity& entity : entities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			collision = CheckCollision_Character(entity, entities);
			movement = GetMovement_Character();
			Update_Character(entity, movement, collision, deltaTime);
			break;
		default:
			break;
		}
	}
}
