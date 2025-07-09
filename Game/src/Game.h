#pragma once

#include "Sprites.h"
#include "Renderer.h"
#include "Entity.h"
#include "World.h"

#include <vector>

class Game
{
public:
	Game() = default;
	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;
	~Game() = default;

	void Run();
private:
	void Init();
	void RunLoop();
	void Close();
private:
	uint32_t m_Width = 1200, m_Height = 900;
	
	Spritesheet m_Spritesheet;
	Renderer m_Renderer{ m_Width, m_Height };
	World m_World{ Vector2{ 0, (float)m_Width }, Vector2{ 0, (float)m_Height } };
};