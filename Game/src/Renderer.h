#pragma once

#include "Sprites.h"
#include "Entity.h"

#include <vector>

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) noexcept = delete;
	~Renderer() = default;

	void RenderEntity(const Entity& entity, 
		const Spritesheet& spritesheet);
	void RenderEntities(const std::vector<Entity>& entities, 
		const Spritesheet& spritesheet);
	void RenderRectangles(const std::vector<Entity>& entities);
};