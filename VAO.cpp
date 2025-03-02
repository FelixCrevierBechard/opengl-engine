#include "VAO.h"

#include<glad/glad.h>
#include"Renderer.h"

VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
	GLCall(glBindVertexArray(m_rendererID));
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VAO::AddBuffer(const VBO& vbo, const VBL& layout) const
{
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];

		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		GLCall(glEnableVertexAttribArray(i));

		offset += element.count * VBE::GetTypeSize(element.type);
	}
}

void VAO::Bind() const
{
	glBindVertexArray(m_rendererID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}