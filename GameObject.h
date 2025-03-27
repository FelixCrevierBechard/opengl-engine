#pragma once

#include "VAO.h"
#include "EBO.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

class GameObject
{
public:
	const char* Name;
	VAO Vao;
	EBO Ebo;

	GameObject(const VAO& vao, const EBO& ebo);
	~GameObject();
};

