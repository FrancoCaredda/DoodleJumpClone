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
	void Update_Character(Entity& entity, float deltaTime);
	void Update_Platform(Entity& platform, const Entity& player, float deltaTime);

	Vector2 GetMovement_Character();
private:
	uint32_t m_Width = 1200, m_Height = 900;
	
	Spritesheet m_Spritesheet;
	Renderer m_Renderer{ m_Width, m_Height };

	float m_PlatformScroll = 0;

	std::vector<Entity> m_Enitities;
};