#pragma once

#include<glad/glad.h>

#include"VBO.h"
#include"VBL.h"
#include"VAO.h"
#include"EBO.h"
#include"Shader.h"
#include"GameObject.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const;
	void Draw(const GameObject& gameObject, Shader& shader) const;
};

