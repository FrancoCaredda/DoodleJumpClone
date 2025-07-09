#pragma once

#include "Sprites.h"
#include "Entity.h"

#include <vector>

class Renderer
{
public:
	Renderer(uint32_t framebufferWidth, uint32_t framebufferHeight)
		: m_FramebufferWidth(framebufferWidth), m_FramebufferHeight(framebufferHeight) {}
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) noexcept = delete;
	~Renderer() = default;

	void RenderFrame(const std::vector<Entity>& entities, int score, const Spritesheet& spritesheet);
	void RenderGameOverScreen();
private:
	void BakeBackground();

	void RenderBackground();
	void RenderEntity(const Entity& entity,
		const Spritesheet& spritesheet);
	void RenderEntities(const std::vector<Entity>& entities,
		const Spritesheet& spritesheet);
	void RenderRectangles(const std::vector<Entity>& entities);
private:
	uint32_t m_FramebufferWidth;
	uint32_t m_FramebufferHeight;

	uint32_t m_BackgroundLinesCount = 50;

	RenderTexture2D m_BackgroundFramebuffer;
};