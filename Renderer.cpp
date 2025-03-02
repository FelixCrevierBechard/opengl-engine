
#include "Renderer.h"

void GLClearError()
{
	while (glGetError());
}
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl error] (0x" << std::hex << error << std::dec << "): "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const
{
	shader.use();
	vao.Bind();
	ebo.Bind();
	glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
	vao.Unbind();
}
