#pragma once

#include"VBO.h"
#include"VBL.h"

class VAO
{
private:
	unsigned int m_rendererID;
public:
	VAO();
	~VAO();

	void AddBuffer(const VBO& vbo, const VBL& layout) const;
	void AddBuffer(const VBO& vbo, const void* vertices, const void* uv) const;

	void Bind() const;
	void Unbind() const;
};

