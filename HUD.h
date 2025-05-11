#pragma once
#include "VAO.h"
#include "Texture.h"

class HUD
{
public:
	VAO Vao;
	Texture Text;

	glm::vec2 Positon = { 0, 0 };
	glm::vec2 Rotation = { 0, 0 };
	glm::vec2 Scale = { 1, 1 };
};

