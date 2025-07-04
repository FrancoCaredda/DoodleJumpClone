#pragma once

#include "Sprites.h"
#include "Entity.h"
#include "Renderer.h"

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

	void UpdateLogic(float deltaTime);
private:
	uint32_t m_Width = 1200, m_Height = 900;
	
	Spritesheet m_Spritesheet;
	Renderer m_Renderer{ m_Width, m_Height };

	float m_Scroll = 0;

	std::vector<Entity> m_Enitities;
};