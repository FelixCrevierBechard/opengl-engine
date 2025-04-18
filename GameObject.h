#pragma once

#include "VAO.h"
#include "EBO.h"
#include "Texture.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

class GameObject
{
public:
	const char* _Name;
	VAO _Vao;
	EBO _Ebo;
	Texture _Text;

	glm::vec3 Positon = {0, 0, 0};
	glm::vec3 Rotation = { 0, 0, 0 };
	glm::vec3 Scale = { 1, 1, 1 };

	GameObject(const char* name, const VAO& vao, const EBO& ebo, const Texture& Texture);
	~GameObject();
};

