#pragma once

#include<glad/glad.h>

#include"Shader.h"
#include"GameObject.h"
#include"Camera.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
	unsigned int default_vao;
public:
	Renderer() {
		glGenVertexArrays(1, &default_vao);
		glBindVertexArray(default_vao);
	}
	~Renderer() {}
	void Draw(GameObject& gameObject, Shader& shader);
	void Draw(std::vector<GameObject> gameObjects, Shader& shader);
	void SetCurrentCamera(Shader& shader, Camera& newCam) const;
};

