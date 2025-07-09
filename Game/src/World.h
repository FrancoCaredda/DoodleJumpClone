#pragma once

#include "Entity.h"

#include <vector>

class World
{
public:
	/*
	* @param horizontalBounds: defines the left and the right of the world;
	* @param verticalBound: defines the top and the bottom of the world
	*/
	World(const Vector2& horizontalBounds, const Vector2& verticalBounds)
		: m_HorizontalBounds{ horizontalBounds }, m_VerticalBounds{ verticalBounds } {}

	void Init();

	void Update(float deltaTime);
	void CleanUp();

	inline bool LoseConditionMet() const { return m_Entities[0].Position.y > m_VerticalBounds.y; }

	inline const std::vector<Entity>& GetEntities() const { return m_Entities; }
	inline int GetScore() const { return m_Score; }
private:
	void ApplyGravity(Entity& entity, float deltaTime);
	void ApplyMovement(Entity& entity, float direction, float deltaTime);
	void ApplyBounciness(Entity& entity);

	bool CheckCollision(const Entity& entity1, const Entity& entity2);

	bool HasEntityCollidedWithWorld(Entity& entity);

	void UpdateScroll(float deltaTime);
	void UpdateCharacter(Entity& entity, float deltaTime);
	void UpdatePlatform(Entity& platform, const Vector2& spawnPosition);
private:
	Vector2 m_HorizontalBounds;
	Vector2 m_VerticalBounds;

	const float m_ScrollSpeed = 1.75f;
	const float m_ScoreAcceptanceTime = 0.5f;
	float m_Scroll = 0;

	int m_Score = 0;

	std::vector<Entity> m_Entities;
};