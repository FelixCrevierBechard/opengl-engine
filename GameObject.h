#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>
#include"VAO.h"
#include"EBO.h"

class GameObject
{
public:
	const char* Name;
	VAO Vao;
	EBO Ebo;

	GameObject(const VAO& vao, const EBO& ebo);
	~GameObject();
};

