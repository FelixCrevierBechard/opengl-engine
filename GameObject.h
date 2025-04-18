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

	GameObject(const char* name, const VAO& vao, const EBO& ebo, const Texture& Texture);
	~GameObject();
};

