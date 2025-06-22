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
	void Update_Character(Entity& entity, const Vector2& movementDirection, bool collision, float deltaTime);
	bool CheckCollision_Character(Entity& character);
	Vector2 GetMovement_Character();
private:
	Spritesheet m_Spritesheet;
	Renderer m_Renderer{1200, 900};
	std::vector<Entity> m_Enitities;
};