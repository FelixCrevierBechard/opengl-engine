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

	void AddBuffer(const VBO &vbo, const VBL& layout) const;

	void Bind() const;
	void Unbind() const;
};

