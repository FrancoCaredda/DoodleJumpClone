#include "Sprites.h"

#include <iostream>

const Sprite Spritesheet::Doodle1{ Vector2{ 0.0f, 0.0f },   Vector2{ 189.0f, 178.0f } };
const Sprite Spritesheet::Doodle2{ Vector2{ 189.0f, 0.0f }, Vector2{ 187.0f, 176.0f } };
const Sprite Spritesheet::Doodle3{ Vector2{ 376.0f, 0.0f }, Vector2{ 177.0f, 179.0f } };
const Sprite Spritesheet::Doodle4{ Vector2{ 553.0f, 0.0f }, Vector2{ 180.0f, 179.0f } };

Spritesheet::~Spritesheet()
{
	UnloadTexture(m_Texture);
}

void Spritesheet::Load(const char* filepath)
{
	m_Texture = LoadTexture(filepath);
}
