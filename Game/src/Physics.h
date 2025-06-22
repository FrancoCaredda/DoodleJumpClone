#pragma once

#include "Entity.h"

void ApplyGravity(Entity& entity, float deltaTime);
bool CheckCollision(const Entity& entity1, const Entity& entity2,
	uint32_t width, uint32_t height);