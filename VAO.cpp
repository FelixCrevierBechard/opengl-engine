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

void VAO::AddBuffer(const VBO& vbo, const void* vertices, const void* uv) const
{
	Bind();
	vbo.Bind();

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(uv), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(uv), uv);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vertices));
}

void VAO::Bind() const
{
	glBindVertexArray(m_rendererID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}