#pragma once

#include "Sprites.h"
#include "Entity.h"

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
	Spritesheet m_Spritesheet;
	std::vector<Entity> m_Enitities;
};