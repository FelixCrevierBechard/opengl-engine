#pragma once

#include<map>
#include<vector>

#include"Shader.h"
#include"Camera.h"
#include"Texture.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class RendererObject {
private:
	// Private members for RendererObject can be added here if needed
public:
	unsigned int ebo;
	unsigned int indexCount;
	std::map<const char*, unsigned int> vbos;
	Texture texture;
	glm::mat4 model = glm::mat4(1.f); // Model matrix for transformations

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

	void set_model(glm::mat4 modelMatrix) { model = modelMatrix; }
};

class Renderer
{
private:
	unsigned int defaultVao;
public:
	Renderer() {
		glGenVertexArrays(1, &defaultVao);
		glBindVertexArray(defaultVao);
	}
	~Renderer() {}
	void draw(RendererObject ro, Shader& shader);
	void draw(std::vector<RendererObject>& ro, Shader& shader);
	void set_currentcamera(Shader& shader, Camera& newCam) const;
};

