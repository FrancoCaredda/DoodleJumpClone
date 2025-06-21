#pragma once

#include "raylib.h"

#include <cstdint>
#include <filesystem>

struct Sprite
{
	Vector2 Offset;
	Vector2 Size;
};

class Spritesheet
{
public:
	Spritesheet() = default;
	Spritesheet(const Spritesheet&) = delete;
	Spritesheet(Spritesheet&&) noexcept = delete;
	~Spritesheet();

	void Load(const char* filepath);

	inline const Texture2D& GetTexture() const { return m_Texture; }
public:
	static const Sprite Doodle1;
	static const Sprite Doodle2;
	static const Sprite Doodle3;
	static const Sprite Doodle4;
private:
	Texture2D m_Texture;
};