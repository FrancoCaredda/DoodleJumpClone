#include "World.h"

void World::Init()
{
	m_Entities.reserve(10);

	m_Entities.emplace_back(Entity{
		Vector2{ 600, 450 },
		Vector2{ 0.5f, 0.5f },
		&Spritesheet::Doodle1,
		Vector2{ 10.0f, 0.0f },
		Vector2{ 0.0f, 40.0f },
		20.0f,
		true,
		true,
		true,
		EntityType::Character
	});

	m_Entities.emplace_back(Entity{
		Vector2{ 600, 800 },
		Vector2{ 0.5f, 0.5f },
		&Spritesheet::Platform1,
		Vector2{ 0.0f, 0.0f },
		Vector2{ 0.0f, 0.0 },
		0.0f,
		true,
		false,
		false,
		EntityType::Platform
	});

	for (int i = 0; i < 9; i++)
	{
		m_Entities.emplace_back(Entity{
			Vector2{ static_cast<float>(rand() % (int)m_HorizontalBounds.y), 
			static_cast<float>(rand() % (int)m_VerticalBounds.y) },
			Vector2{ 0.5f, 0.5f },
			&Spritesheet::Platform1,
			Vector2{ 0.0f, 0.0f },
			Vector2{ 0.0f, 0.0 },
			0.0f,
			true,
			false,
			false,
			EntityType::Platform
		});
	}
}

void World::Update(float deltaTime)
{
	static Vector2 position{};
	static Vector2 velocity{};

	if (position.y < m_VerticalBounds.y / 2.0f && velocity.y < 0)
	{
		m_Scroll += -velocity.y * 1.75f * deltaTime;
	}
	else
	{
		m_Scroll = 0;
	}

	UpdateScroll();

	for (Entity& entity : m_Entities)
	{
		switch (entity.Type)
		{
		case EntityType::Character:
			position = entity.Position;
			velocity = entity.Velocity;
			ApplyGravity(entity, deltaTime);
			UpdateCharacter(entity, deltaTime);
			break;
		case EntityType::Platform:
			UpdatePlatform(entity, position);
			break;
		default:
			break;
		}
	}
}

void World::CleanUp()
{
	m_Entities.clear();
	m_Scroll = 0;
}

void World::ApplyGravity(Entity& entity, float deltaTime)
{
	if (!entity.bFalling)
	{
		return;
	}

	float gravity = entity.Acceleration.y * deltaTime;
	float newVelocity = entity.Velocity.y + gravity;

	float newPosition = entity.Position.y + newVelocity;
	entity.Velocity.y = newVelocity;
	entity.Position.y = newPosition;
}

void World::ApplyMovement(Entity& entity, float direction, float deltaTime)
{
	float acceleration = entity.Acceleration.x * deltaTime;
	float newVelocity = entity.Velocity.x + acceleration;

	float newPosition = entity.Position.x + direction * newVelocity;
	entity.Velocity.x = newVelocity;
	entity.Position.x = newPosition;
}

void World::ApplyBounciness(Entity& entity)
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

bool World::CheckCollision(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.bSolid || !entity2.bSolid)
	{
		return false;
	}

	Rectangle BoundingBox1 = CalculateBoundingBox(entity1);
	Rectangle BoundingBox2 = CalculateBoundingBox(entity2);

	return CheckCollisionRecs(BoundingBox1, BoundingBox2);
}

bool World::HasEntityCollidedWithWorld(Entity& entity)
{
	for (const Entity& currentEntity : m_Entities)
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

void World::UpdateScroll()
{
	for (Entity& entity : m_Entities)
	{
		entity.Position.y += m_Scroll;
	}
}

void World::UpdateCharacter(Entity& entity, float deltaTime)
{
	if (HasEntityCollidedWithWorld(entity) && entity.Velocity.y > 0.0f)
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

	if (entity.Position.x > m_HorizontalBounds.y)
	{
		entity.Position.x = m_HorizontalBounds.x;
	}

	if (entity.Position.x < m_HorizontalBounds.x)
	{
		entity.Position.x = m_HorizontalBounds.y;
	}
}

void World::UpdatePlatform(Entity& platform, const Vector2& spawnPosition)
{
	if ((uint32_t)platform.Position.y > m_VerticalBounds.y)
	{
		platform.Position.y = spawnPosition.y - (rand() % 50);
	}
}