#pragma once

#include<glad/glad.h>
#include<map>

#include"Shader.h"
#include"GameObject.h"
#include"Camera.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class RendererObject {
public:
	unsigned int indexCount;
	unsigned int ebo;
	std::map<const char*, unsigned int> vbos;
	Texture texture;

	RendererObject(std::vector<unsigned int>& indices, std::vector<float>& vertices, std::vector<float>& uv, Texture& texture) : texture(texture) {
		indexCount = indices.size();
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, indices.data(), GL_STATIC_DRAW);

		unsigned int vert, UV;
		glGenBuffers(1, &vert);
		glBindBuffer(GL_ARRAY_BUFFER, vert);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_STATIC_DRAW);
		vbos["vert"] = vert;

		glGenBuffers(1, &UV);
		glBindBuffer(GL_ARRAY_BUFFER, UV);
		glBufferData(GL_ARRAY_BUFFER, uv.size() * 4, uv.data(), GL_STATIC_DRAW);
		vbos["uv"] = UV;
	}
	~RendererObject() {}
};

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
	void Draw(RendererObject ro, Transform transform, Shader& shader);
	void Draw(std::vector<GameObject> gameObjects, Shader& shader);
	void SetCurrentCamera(Shader& shader, Camera& newCam) const;
};

